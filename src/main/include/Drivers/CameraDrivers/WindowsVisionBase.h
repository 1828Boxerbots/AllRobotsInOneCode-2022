#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
//#include <cameraserver/CameraServer.h>
#include <frc/Timer.h>
#include <cameraserver/CameraServer.h>
#include "Util.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class WindowsVisionBase
{

//#define M_WINDOWS

public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="index"> 0 = webcam, 1 = USB camera </param>
	WindowsVisionBase(int index, bool slider);

	/// <summary>
	/// Initialize Hardware
	/// </summary>
	/// <returns>
	///		true = initialization successful
	///		false = error occured
	/// </returns>
	virtual bool Init();

	/// <summary>
	/// Which direction should the robot turn and how fast
	/// </summary
	/// 
	/// <returns>
	///		range is -1.0 to +1.0, negative value is turn left
	/// </returns>
	double WhereToTurn(double deadZoneLocation = 0.0, int deadZoneRange = 100);

	enum VisionColors{ RED_CONE, GREEN_CONE, YELLOW_CONE, ORANGE_CONE };

	virtual void Tick();

protected:
	int m_frameCounter = 0;

	//Values that it is filtering by
	const cv::Scalar GREEN_CONE_LOW{ 38, 127, 123 };
	const cv::Scalar GREEN_CONE_HIGH{ 79,255,255 };
	const cv::Scalar RED_CONE_LOW{ 0,134,120 };
	const cv::Scalar RED_CONE_HIGH{ 6,255,255 };

	const cv::Scalar YELLOW_CONE_LOW{ 22, 134,139 };
	const cv::Scalar YELLOW_CONE_HIGH{ 42,255,255 };
	const cv::Scalar ORANGE_CONE_LOW{ 0,76,255 };
	const cv::Scalar ORANGE_CONE_HIGH{ 21,255,255 };

	cv::Scalar m_resultL = GREEN_CONE_LOW;
	cv::Scalar m_resultH = GREEN_CONE_HIGH;

	//Window Names
	const std::string IMAGE_LINE = "Line Image";
	const std::string IMAGE_THRESHOLD = "Threshold";
	const std::string IMAGE_HSV = "HSV Image";
	const std::string SLIDERS_WINDOW = "Control";

	//The index/port of the camera - given in the constructor
	int m_index;
	bool m_seeSlider = false;
	//The points that hold the center of blob
	double m_centroidX;
	double m_centroidY;

	//What color are we looking for?
	VisionColors m_visionColor = VisionColors::GREEN_CONE;

	//Holds the camera and raw image
	cv::Mat m_frame;
	cv::Mat m_imgHSV;
	cv::Mat m_imgThresholded;
	frc::Timer timer;
	#ifdef M_WINDOWS
		cv::VideoCapture m_camera;
	#else
	cs::UsbCamera m_camera;
	cs::CvSink m_cvSink;
	cs::CvSource m_outputStreamLine;
	cs::CvSource m_outputStreamThreshold;
	cs::CvSource m_outputStreamHSV;
	#endif

	/// <summary>
	/// Create a new window to display an image
	/// </summary>
	/// <param name="title">String of what the window is called</param>
	/// <param name="frame">The image that should be displayed</param>
	virtual void SendImage(std::string title, cv::Mat frame);

	/// <summary>
	/// Find the blob on the image
	/// </summary>
	/// <returns>True - The image is fine  False - The image is empty </returns>
	bool GetBlob(int deadZonePixel);

	/// <summary>
	/// Filters the image and gets the position of its center
	/// </summary>
	void SetColor();

	void AddSliders();

	virtual bool GrabFrame();

	virtual void Log(std::string title, std::string value);
	virtual void Log(std::string title, double value);
	virtual void Log(std::string title, int value);
};

