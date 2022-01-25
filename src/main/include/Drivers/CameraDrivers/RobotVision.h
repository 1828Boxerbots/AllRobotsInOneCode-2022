#pragma once
#include "WindowsVisionBase.h"
#include <cameraserver/CameraServer.h>
#include "Util.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class RobotVision : public WindowsVisionBase
{
public:
	RobotVision(int port);
	bool Init() override;
	void Tick() override;
private:
	void SendImage(std::string title, cv::Mat frame) override;
    bool GrabFrame() override;

	void Log(std::string title, std::string value) override;
	void Log(std::string title, double value) override;
	void Log(std::string title, int value) override;

	//The points that hold the center of blob
	double m_centroidX;
	double m_centroidY;

	//Holds the camera and raw image
	cs::UsbCamera m_camera;
	cs::CvSink m_cvSink;
	cs::CvSource m_outputStreamLine;
	cs::CvSource m_outputStreamThreshold;
	cs::CvSource m_outputStreamHSV;
};

