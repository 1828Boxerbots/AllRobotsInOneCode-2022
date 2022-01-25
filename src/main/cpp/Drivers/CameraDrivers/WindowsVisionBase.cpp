#include "../../../include/Drivers/CameraDrivers/WindowsVisionBase.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

WindowsVisionBase::WindowsVisionBase(int port, bool slider)
{
	m_index = port;
	m_seeSlider = slider;
}

bool WindowsVisionBase::Init()
{
	//m_camera = frc::CameraServer::StartAutomaticCapture();
	//m_camera.SetResolution(640, 480);
	//m_cvSink = frc::CameraServer::GetVideo();
	//m_outputStream = frc::CameraServer::PutVideo(IMAGE_FILTERED, 640, 480);
	//m_outputStreamTwo = frc::CameraServer::PutVideo(IMAGE_THRESHOLD, 640, 480);

	#ifdef M_WINDOWS
	if (m_camera.open(m_index) == 0)
	{
		return false;
	}
	
	AddSliders();
	#else
	m_camera = frc::CameraServer::GetInstance() -> StartAutomaticCapture();
	m_camera.SetResolution(640,480);
	m_cvSink = frc::CameraServer::GetInstance() -> GetVideo();
	m_outputStreamLine = frc::CameraServer::PutVideo(IMAGE_LINE, 640, 480);
	m_outputStreamThreshold = frc::CameraServer::PutVideo(IMAGE_THRESHOLD, 640, 480);
	m_outputStreamHSV = frc::CameraServer::PutVideo(IMAGE_HSV, 640, 480);
	#endif

	return true;
}

void WindowsVisionBase::Tick()
{
	#ifdef M_WINDOWS
		GetBlob(1);
	#else
		if(GrabFrame() == false)
		{
			return;
		}
		cv::line(m_frame, cv::Point(0, 0), cv::Point(m_frame.size().width, m_frame.size().height), cv::Scalar(0, 0, 255), 3);
		SendImage(IMAGE_LINE, m_frame);
	#endif
}

//deadZone can be a range of -1 to 1
double WindowsVisionBase::WhereToTurn(double deadZoneLocation, int deadZoneRange)
{
	Log("Vision Frame Counter", m_frameCounter++);
	Log("Shadow 2", "WhereToTurn-1");

	double screenCenter = m_frame.size().width / 2;
	int deadZone2 = (deadZoneLocation * screenCenter) + screenCenter;

	//Check if there is a blob
	if (GetBlob(deadZone2) == false /*|| m_centroidX == nan( && m_centroidY == nan(ind)*/)
	{
		Log("Shadow 2", "WhereToTurn-3");
		return -2.0;
	}

	//Use some MATH to turn the deadZone from a percentage to the size of the screen

	//Get Dead zone values
	int highDedZone = deadZone2 + deadZoneRange;
	int lowDedZone = deadZone2 - deadZoneRange;
	//Check if we are in the dead zone
	if (m_centroidX > lowDedZone && m_centroidX < highDedZone)
	{
		Log("Shadow 2", "WhereToTurn-4");
		return 0.0;
	}

	//Use some MATH to turn our position into a percentage and return
	double powerPercentage = ((m_centroidX - screenCenter) / screenCenter) - deadZoneLocation;
	if (powerPercentage > 1.0)
	{
		powerPercentage = 1.0;
	}
	if (powerPercentage < -1.0)
	{
		powerPercentage = -1.0;
	}
	// cv::Mat textImg = m_frame;
	// cv::QtFont font;
	// std::string powerPercentageStr = std::to_string(powerPercentage);

	// cv::putText(textImg, powerPercentageStr, cv::Point(m_centroidX, m_centroidY), cv::FONT_HERSHEY_SIMPLEX, 2.0, cv::Scalar(255, 0, 0), 2);
	// SendImage("TextImage", textImg);

	Log("Shadow 2", "WhereToTurn-2");
	return powerPercentage;
}


void WindowsVisionBase::SendImage(std::string title, cv::Mat frame)
{
	#ifdef M_WINDOWS
		cv::imshow(title.c_str(), frame);
	#else
		if(title == IMAGE_LINE)
		{
			m_outputStreamLine.PutFrame(frame);
		}
		else if(title == IMAGE_THRESHOLD)
		{
			m_outputStreamThreshold.PutFrame(frame);
		}
		else if(title == IMAGE_HSV)
		{
			m_outputStreamHSV.PutFrame(frame);
		}
		else
		{
			m_outputStreamLine.PutFrame(frame);
		}
	#endif
}

bool WindowsVisionBase::GrabFrame()
{
	#ifdef M_WINDOWS
		m_camera >> m_frame;

		if (m_frame.empty())
		{
			return false;
		}
	#else
		if(m_cvSink.GrabFrame(m_frame) == 0)
		{
			return false;
		}
	#endif
	return true;
}

void WindowsVisionBase::Log(std::string title, std::string value)
{
	#ifdef M_WINDOWS
	std::cout << title << ": " << value << "\n";
	#else
	Util::Log(title, value);
	#endif
}
void WindowsVisionBase::Log(std::string title, int value)
{
	#ifdef M_WINDOWS
	std::cout << title << ": " << value << "\n";
	#else
	Util::Log(title, value);
	#endif
}
void WindowsVisionBase::Log(std::string title, double value)
{
	#ifdef M_WINDOWS
	std::cout << title << ": " << value << "\n";
	#else
	Util::Log(title, value);
	#endif
}

bool WindowsVisionBase::GetBlob(int deadZonePixel)
{
	Log("Shadow 2", "GetBlob-1");
	//Gets one frame from camera
	if (GrabFrame() == false)
	{
		Log("Shadow 2", "WhereToTurn-3");
		return false;
	}
	timer.Reset();
	timer.Start();

	//Filter the image
	SetColor();

	if (m_centroidY > 0.0 && m_centroidX > 0.0)
	{
		//Place a 2 line where the blob is
		switch (m_visionColor)
		{
		case VisionColors::GREEN_CONE:
			cv::line(m_frame, cv::Point(0, m_centroidY), cv::Point(m_frame.size().width, m_centroidY), cv::Scalar(0, 255, 0), 3);
			cv::line(m_frame, cv::Point(m_centroidX, 0), cv::Point(m_centroidX, m_frame.size().height), cv::Scalar(0, 255, 0), 3);
			break;
		case VisionColors::RED_CONE:
			cv::line(m_frame, cv::Point(0, m_centroidY), cv::Point(m_frame.size().width, m_centroidY), cv::Scalar(0, 0, 255), 3);
			cv::line(m_frame, cv::Point(m_centroidX, 0), cv::Point(m_centroidX, m_frame.size().height), cv::Scalar(0, 0, 255), 3);
			break;
		default:
			cv::line(m_frame, cv::Point(0, m_centroidY), cv::Point(m_frame.size().width, m_centroidY), cv::Scalar(0, 0, 255), 3);
			cv::line(m_frame, cv::Point(m_centroidX, 0), cv::Point(m_centroidX, m_frame.size().height), cv::Scalar(0, 0, 255), 3);
			break;
		}

		//Show where deadzone is
		cv::line(m_frame, cv::Point(deadZonePixel, 0), cv::Point(deadZonePixel, m_frame.size().height), cv::Scalar(255, 0, 0), 3);
	}
	else
	{
		SendImage(IMAGE_LINE, m_frame);
		Log("Shadow 2", "WhereToTurn-4");
		return false;
	}
	// //Display the new image
	SendImage(IMAGE_LINE, m_frame);

	cv::waitKey(1);

	//Checks is there is no blob
	// if (isnan(m_centroidX) && isnan(m_centroidY))
	// {
	// 	return false;
	// }

	Log("Shadow 2", "WhereToTurn-2");
	return true;
}

void WindowsVisionBase::SetColor()
{
	Log("Shadow 2", "SetColor-1");
	//Change the camera image from BGR to HSV - Blue Green Red to Hue Saturation Value
	cv::cvtColor(m_frame, m_imgHSV, cv::COLOR_BGR2HSV);
	//SendImage("grey image", imgHSV);

	// if (m_seeSlider == true)
	// {
	// 	//AddSliders();
	// }
	// else
	{
		//Looks for specifc colors in the image
		Log("Shadow 2", "WhereToTurn-Begin Switch");
		switch (m_visionColor)
		{
		case VisionColors::GREEN_CONE:
			m_resultL = GREEN_CONE_LOW;
			m_resultH = GREEN_CONE_HIGH;
			break;
		case VisionColors::RED_CONE:
			m_resultL = RED_CONE_LOW;
			m_resultH = RED_CONE_LOW;
			break;
		case VisionColors::YELLOW_CONE:
			m_resultL = YELLOW_CONE_LOW;
			m_resultH = YELLOW_CONE_LOW;
			break;
		case VisionColors::ORANGE_CONE:
			m_resultL = ORANGE_CONE_LOW;
			m_resultH = ORANGE_CONE_LOW;
			break;
		default:
			m_resultL = GREEN_CONE_LOW;
			m_resultH = GREEN_CONE_LOW;
			break;
		}
		Log("Shadow 2", "WhereToTurn-End Switch");
	}
	cv::inRange(m_imgHSV, m_resultL, m_resultH, m_imgThresholded);

	//units::second_t time = timer.Get();
	//Log("Vision Timer", time);
	timer.Stop();
	//Display Filtered Image
	SendImage(IMAGE_THRESHOLD, m_imgThresholded);
	// Find moments of the image
	cv::Moments m = cv::moments(m_imgThresholded, true);
	if (m.m00 != 0)
	{
		m_centroidX = m.m10 / m.m00;
		m_centroidY = m.m01 / m.m00;
		cv::Point p(m_centroidX, m_centroidY);
	}
	else
	{
		m_centroidX = -1.0;
		m_centroidY = -1.0;
	}
	Log("Shadow 2", "WhereToTurn-2");
}

void WindowsVisionBase::AddSliders()
{
	//cv::namedWindow(SLIDERS_WINDOW, cv::WINDOW_AUTOSIZE);
	//int lowHue = m_resultL.val[0];
	//int highHue = m_resultH.val[0];
	//int lowSat = m_resultL.val[1];
	//int highSat = m_resultH.val[1];
	//int lowVal = m_resultL.val[2];
	//int highVal = m_resultH.val[2];

	//cv::createTrackbar("LowH", SLIDERS_WINDOW, &lowHue, 179); //Hue (0-179)
	//cv::createTrackbar("HighH", SLIDERS_WINDOW, &highHue, 255);
	//cv::createTrackbar("LowS", SLIDERS_WINDOW, &lowSat, 255); //Saturation (0-255)
	//cv::createTrackbar("HighS", SLIDERS_WINDOW, &highSat, 255);
	//cv::createTrackbar("LowV", SLIDERS_WINDOW, &lowVal, 255); //Value (0-255)
	//cv::createTrackbar("HighV", SLIDERS_WINDOW, &highVal, 255);

	//m_resultL.val[0] = lowHue;
	//m_resultH.val[0] = highHue;
	//m_resultL.val[1] = lowSat;
	//m_resultH.val[1] = highSat;
	//m_resultL.val[2] = lowVal;
	//m_resultH.val[2] = highVal;
}