#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include "../../Constants.h"
#include <cameraserver/CameraServer.h>


class CameraVision
{
	//#define M_WINDOWS

public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="index"> 0 = webcam, 1 = USB camera </param>
	CameraVision(int index);

	/// <summary>
	/// Initialize Hardware
	/// </summary>
	/// <returns>
	///		true = initialization successful
	///		false = error occured
	/// </returns>
	bool Init();

	/// <summary>
	/// Which direction should the robot turn and how fast
	/// </summary
	/// 
	/// <returns>
	///		range is -1.0 to +1.0, negative value is turn left
	/// </returns>
	double WhereToTurn( double deadZoneLocation = 0.0, int deadZoneRange = 100);

	enum VisionColors{RED_CONE, GREEN_CONE, YELLOW_CONE, ORANGE_CONE};

	void Tick();

private:
 	int m_frameCounter = 0;

	// const int LOWH_GREEN_CONE  = 38;
	// const int HIGHH_GREEN_CONE  = 79;
	// const int LOWS_GREEN_CONE  = 127;
	// const int HIGHS_GREEN_CONE  = 255;
	// const int LOWV_GREEN_CONE = 123;
	// const int HIGHV_GREEN_CONE = 255;

	// const int LOWH_RED_CONE  = 0;
	// const int HIGHH_RED  = 6;
	// const int LOWS_RED  = 134;
	// const int HIGHS_RED  = 255;
	// const int LOWV_RED  = 120;
	// const int HIGHV_RED  = 255;

	const cv::Scalar GREEN_CONE_LOW{38, 127, 123};
	const cv::Scalar GREEN_CONE_HIGH{79,255,255};
	const cv::Scalar RED_CONE_LOW{0,134,120};
	const cv::Scalar RED_CONE_HIGH{6,255,255};

	const cv::Scalar YELLOW_CONE_LOW{22, 134,139};
	const cv::Scalar YELLOW_CONE_HIGH{42,255,255};
	const cv::Scalar ORANGE_CONE_LOW{0,76,255};
	const cv::Scalar ORANGE_CONE_HIGH{21,255,255};

	const std::string IMAGE_FILTERED = "Filtered";
	const std::string IMAGE_THRESHOLD = "Threshold";

	//The index/port of the camera - given in the constructor
	int m_index;

	//The points that hold the center of blob
	double m_centroidX;
	double m_centroidY;

	//How big is the dead zone where WhereToTurn() = 0.0
	//double m_deadZone = 50.0;

	VisionColors m_visionColor = GREEN_CONE;

	//Holds the camera and raw image
	cv::Mat m_frame;
	cv::Mat m_imgHSV;
	cv::Mat m_imgThresholded;
	#ifndef M_WINDOWS
	cs::UsbCamera m_camera;
	cs::CvSink m_cvSink;
	cs::CvSource m_outputStream;
	cs::CvSource m_outputStreamTwo;
	#else
	cv::VideoCapture m_camera;
	#endif

	/// <summary>
	/// Create a new window to display an image
	/// </summary>
	/// <param name="title">String of what the window is called</param>
	/// <param name="frame">The image that should be displayed</param>
	void SendImage(std::string title, cv::Mat frame/*, int width, int height*/);

	/// <summary>
	/// Find the blob on the image
	/// </summary>
	/// <returns>True - The image is fine  False - The image is empty </returns>
	bool GetBlob(int deadZonePixel);

	/// <summary>
	/// Filters the image and gets the position of its center
	/// </summary>
	void SetColor();

	bool GrabFrame();

	void Log(std::string title, std::string value);
	void Log(std::string title, double value);
	void Log(std::string title, int value);
};

