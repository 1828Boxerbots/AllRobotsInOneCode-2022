#include "Drivers/CameraDrivers/RobotVision.h"
#include <opencv2/imgproc/imgproc.hpp>


RobotVision::RobotVision(int port) : WindowsVisionBase(port, false)
{
	
}

bool RobotVision::Init()
{
	Util::Log("Shadow RV", "RobotVision Init-1");
	m_camera = frc::CameraServer::GetInstance() -> StartAutomaticCapture();
	m_camera.SetResolution(640,480);
	m_cvSink = frc::CameraServer::GetInstance() -> GetVideo();
	m_outputStreamLine = frc::CameraServer::PutVideo(IMAGE_LINE, 640, 480);
	m_outputStreamThreshold = frc::CameraServer::PutVideo(IMAGE_THRESHOLD, 640, 480);
	m_outputStreamHSV = frc::CameraServer::PutVideo(IMAGE_HSV, 640, 480);
	Util::Log("Shadow RV", "RobotVision Init-2");
	return true;
}

void RobotVision::Tick()
{
	Util::Log("Shadow RV", "RobotVision Tick-1");
	if(GrabFrame() == false)
    {
        return;
    }

	cv::line(m_frame, cv::Point(0, 0), cv::Point(m_frame.size().width, m_frame.size().height), cv::Scalar(0, 0, 255), 3);

	//m_outputStream.PutFrame(m_frame);
	SendImage(IMAGE_LINE, m_frame);

	Util::Log("Shadow RV", "RobotVision Tick-2");
}

void RobotVision::SendImage(std::string title, cv::Mat frame)
{
	Util::Log("Shadow RV", "RobotVision SendImage-1");
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
	Util::Log("Shadow RV", "RobotVision SendImage-2");
}

bool RobotVision::GrabFrame()
{
	if(m_cvSink.GrabFrame(m_frame) == 0)
	{
		return false;
	}
	return true;

	// Util::Log("Shadow RV", "RobotVision GetImage-1");
    // if (m_cvSink.GrabFrame(m_frame) == 0)
	// {
	// 	Util::Log("Shadow RV", "RobotVision GetImage-3");
	// 	return false;
	// }
	// Util::Log("Shadow RV", "RobotVision GetImage-2");
    // return true;
}

void RobotVision::Log(std::string title, std::string value)
{
	Util::Log(title, value);
}
void RobotVision::Log(std::string title, double value)
{
	Util::Log(title, value);
}
void RobotVision::Log(std::string title, int value)
{
	Util::Log(title, value);
}