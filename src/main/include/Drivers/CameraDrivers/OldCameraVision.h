#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include "../../Constants.h"
#include <cameraserver/CameraServer.h>


class OldCameraVision
{
private:
	//CAMERA RESOLUTION
	const static int M_CAMERA_HEIGHT = 240;
	const static int M_CAMERA_WIDTH = 320;

public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="index"> 0 = webcam, 1 = USB camera </param>
	OldCameraVision(int index);

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

	void SetCrop(int cropX = 0, int cropY = 0, int cropW = M_CAMERA_WIDTH, int cropH = M_CAMERA_HEIGHT);
	void GetSize(int *pHeight, int *pWidth);

	enum VisionColors{INVALID_COLOR, RED_CONE_M, RED_CONE_A, RED_CONE_N
	, GREEN_CONE_M, GREEN_CONE_A, GREEN_CONE_N
	, YELLOW_LEMON_M, YELLOW_LEMON_A, YELLOW_LEMON_N
	, PURPLE_BOTTLE_M, PURPLE_BOTTLE_A, PURPLE_BOTTLE_N
	, LEMON_ROCKY_M, LEMON_ROCKY_A, LEMON_ROCKY_N
	, YELLOW_CONE, ORANGE_CONE
	, REF_GREEN
	, FMS_COLOR};

	void Tick();
	
	void SetHigh(int HSV, int value);
	void SetLow(int HSV, int value);

	void SetFMSColor(VisionColors color);

	void SetLookingColor(VisionColors color);
	VisionColors GetLookingColor();

	double GetCentroidX();
	double GetCentroidY();

	//Check Vars
	double m_minArea = 0;			// 5-22-2021 Ref-Green values in MPR Lights ON
	double m_maxArea = 30000;		// C-500-3000-1-3-0-1
	double m_minRatio = 1;
	double m_maxRatio = 3;			// 6-19-2021 Contour values for ref-green in build room
	double m_minSolid = 0;			// C-200-5000-1-2-0-0.34
	double m_maxSolid = 1;
	double m_saveCheck[6] = {200, 5000, 1, 2, 0, 0.34};

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

	//Green Cone Values
	const cv::Scalar GREEN_CONE_LOW_M{30, 107, 103};	//Morning	//V-30-79-107-255-103-255
	const cv::Scalar GREEN_CONE_HIGH_M{79,255,255};		//Morning
	const cv::Scalar GREEN_CONE_LOW_A{30, 107, 103};	//Afternoon	//V-30-79-107-255-103-255	 // 2/12/2021 Time 2:37PM
	const cv::Scalar GREEN_CONE_HIGH_A{79,255,255};		//Afternoon
	const cv::Scalar GREEN_CONE_LOW_N{30, 107, 103};	//Night		//V-30-79-107-255-103-255
	const cv::Scalar GREEN_CONE_HIGH_N{79,255,255};		//Night

	//Red Cone Values
	const cv::Scalar RED_CONE_LOW_M{3,180,100};			//Morning
	const cv::Scalar RED_CONE_HIGH_M{10,255,255};		//Morning
	const cv::Scalar RED_CONE_LOW_A{3,180,100};			//Afternoon
	const cv::Scalar RED_CONE_HIGH_A{10,255,255};		//Afternoon
	const cv::Scalar RED_CONE_LOW_N{3,180,100};			//Night		//V-3-10-180-255-100-255
	const cv::Scalar RED_CONE_HIGH_N{10,255,255};		//Night

	//Yellow Lemon Values
	const cv::Scalar YELLOW_LEMON_LOW_M{14, 100, 150};	  //Moring		//V-14-30-100-255-150-255
	const cv::Scalar YELLOW_LEMON_HIGH_M{30, 255, 255};  //Moring
	const cv::Scalar YELLOW_LEMON_LOW_A{17, 25, 204};	  //Afternoon	//V-17-179-25-255-204-255 //6:06 2/19/2021
	const cv::Scalar YELLOW_LEMON_HIGH_A{179, 255, 255};  //Afternoon
	const cv::Scalar YELLOW_LEMON_LOW_N{20, 60, 200};     //Night		// V-20-179-60-255-200-255
	const cv::Scalar YELLOW_LEMON_HIGH_N{179, 255, 255};  //Night

	//Purple Bottle Values
	const cv::Scalar PURPLE_BOTTLE_LOW_M{100, 0, 0};			//V-100-150-0-155-0-255
	const cv::Scalar PURPLE_BOTTLE_HIGH_M{150, 155, 255};
	const cv::Scalar PURPLE_BOTTLE_LOW_A{70, 50, 45};			//V-70-150-50-200-45-120
	const cv::Scalar PURPLE_BOTTLE_HIGH_A{150, 200, 120};
	const cv::Scalar PURPLE_BOTTLE_LOW_N{10, 0, 0};			//V-10-20-0-155-0-255
	const cv::Scalar PURPLE_BOTTLE_HIGH_N{20, 155, 255};

	const cv::Scalar YELLOW_CONE_LOW{24, 50,150};  
	const cv::Scalar YELLOW_CONE_HIGH{32,130,255};
	const cv::Scalar ORANGE_CONE_LOW{0,15,170};			
	const cv::Scalar ORANGE_CONE_HIGH{20,255,255};		//V-0-20-15-255-170-255
	const cv::Scalar BLUE_TEAMSHIRT_LOW{50, 50, 100};
	const cv::Scalar BLUE_TEAMSHIRT_HIGH{100, 255, 255};

	//REFLECTIVE GREEN
	const cv::Scalar REF_GREEN_LOW{40, 70, 150};			//V-40-80-50-180-100-255
	const cv::Scalar REF_GREEN_HIGH{100, 255, 255};		//V-40-100-70-255-150-255 = 6-19-2021 Build room val

	//Lemon Rocky
	const cv::Scalar YELLOW_LEMON_LOW_ROCKY_M{14, 100, 150};	//Moring		//V-14-30-100-255-150-255
	const cv::Scalar YELLOW_LEMON_HIGH_ROCKY_M{30, 255, 255};  	//Moring
	const cv::Scalar YELLOW_LEMON_LOW_ROCKY_A{17, 25, 204};	  	//Afternoon	//V-17-179-25-255-204-255 //6:06 2/19/2021
	const cv::Scalar YELLOW_LEMON_HIGH_ROCKY_A{179, 255, 255};  //Afternoon
	const cv::Scalar YELLOW_LEMON_LOW_ROCKY_N{20, 60, 200};     //Night		// V-20-179-60-255-200-255
	const cv::Scalar YELLOW_LEMON_HIGH_ROCKY_N{179, 255, 255};  //Night

	const std::string IMAGE_FILTERED = "Filtered";
	const std::string IMAGE_THRESHOLD = "Threshold";
	const std::string IMAGE_HSV = "HSV";
	const std::string IMAGE_CONT = "Contours";

	cv::Scalar FMS_HIGH{80, 255, 255};		//V-40-80-150-255-100-255
	cv::Scalar FMS_LOW{40, 150, 100};

	const double OUT_OF_CAMERA_RANGE = -3.0;

	//Values that it is filtering by

	//The index/port of the camera - given in the constructor
	int m_index;

	//The points that hold the center of blob
	double m_centroidX;
	double m_centroidY;

	//The thickness of the filter lines in pixels
	const int M_LINE_THICKNESS = 3;

	//The color of the deadzone line
	const cv::Scalar M_DEADZONE_COLOR = cv::Scalar(255, 0, 0); // Currently Blue

	//CAMERA MIDPOINTS
	double m_screenCenterX = ( M_CAMERA_WIDTH / 2 );
	double m_screenCenterY = ( M_CAMERA_HEIGHT / 2 );

	//How big is the dead zone where WhereToTurn() = 0.0
	//double m_deadZone = 50.0;

	VisionColors m_visionColor = REF_GREEN;
	//Holds the camera and raw image
	cv::Mat m_frame; 
	cv::Mat m_imgHSV;
	cv::Mat m_imgThresholded;
	cv::Mat m_imgThresholdedTwo;
	cv::Mat m_imgCanny;
	cv::Mat m_imgContour;
	cv::Mat m_elementE;
	cv::Mat m_elementD;
	cv::Mat m_erode;
	cv::Mat m_dilate;
	cs::UsbCamera m_camera;
	cs::CvSink m_cvSink;
	cs::CvSource m_outputStream;
	cs::CvSource m_outputStreamTwo;
	cs::CvSource m_outputStreamHSV;
	cs::CvSource m_outStreamContour;
	cv::Rect2d m_rect;
	int m_cropX = 0; 
	int m_cropY = 0; 
	int m_cropW = M_CAMERA_WIDTH; 
	int m_cropH = M_CAMERA_HEIGHT;
	int m_erodeSize = 1;
	int m_dilateSize = 3;

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

	void SetColorBGR();

	bool GrabFrame();

	void GetContours();
};

