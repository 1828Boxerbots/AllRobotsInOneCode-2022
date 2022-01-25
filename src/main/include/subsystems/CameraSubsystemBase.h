/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/*
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <opencv2/core.hpp>
#include <opencv2/cvconfig.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <frc/smartdashboard/SmartDashboard.h>
#include <cameraserver/CameraServer.h>
#include "Constants.h"
#include "subsystems/DriveTrainSubsystemBase.h"


//using namespace cv;

class CameraSubsystemBase : public frc2::SubsystemBase {
 public:
  CameraSubsystemBase(DriveTrainSubsystemBase *pDrive);

  void Init();
  int WhereToTurn();
  void Tick();
  void CameraPeriodic();
  void Log(std::string title, double num);
  void Log(std::string title, int  num);
  void Log(std::string title, bool flag);
  void Log(std::string title, std::string str);

  static const int GO_LEFT = 1;
  static const int GO_RIGHT = -1;
  //static onst int GO_RIGHT = 1;
  //static const int GO_LEFT = -1;
  static const int STOP = 0;
  static const int CANT_FIND_IMAGE = -2;

  const int PIXELCOUNT = 50;
  virtual int GetLeftMin() { return 0;}
  virtual int GetLeftMax() { return GetMaxResolutionX()/2 - PIXELCOUNT;}
  virtual int GetCenterMin() { return GetMaxResolutionX()/2 - PIXELCOUNT+1;}
  virtual int GetCenterMax() { return GetMaxResolutionX()/2 + PIXELCOUNT;}
  virtual int GetRightMin() { return GetMaxResolutionX()/2 + PIXELCOUNT + 1;}
  virtual int GetRightMax() { return GetMaxResolutionX();}
  virtual int GetMaxResolutionX() { return m_widthCamera;};
  virtual int GetMaxResolutionY() { return m_heightCamera;};
  virtual void SetColor(int colorNumber = 0);
  void AutoCameraTurn();
  void InitSendImage();

  static void VideoThread(CameraSubsystemBase* pCamera);

  void  TeleopImage();

  protected:

  void InitializeCamera(int port);
  void FilterFrame();
  void PrintTurn(int turn);
  */

/**
   * Will be called periodically whenever the CommandScheduler runs.
   */

/*
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  bool m_stopSendImage = false;
  int m_frameNumber = 1;
  int m_widthCamera = 0;
  int m_heightCamera = 0;
  cv::Mat m_frame;
  cv::Mat m_morph = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3), cv::Point(-1, 1)); 
  cv::Mat m_colorFilter;
  cv::Mat m_dilution;
  cv::Mat m_openFilter;
  cv::Moments m_moment;
  cv::Point m_center;
  cv::Point m_defaultCenter;
  cv::Mat m_output;
  bool m_isInitialized = false;

  bool ouputImagefail = false;
  int m_sendSizeWidth = 480;
  int m_sendSizeHeight = 640;
  int m_sendRectWidth = m_sendSizeWidth/2;
  int m_sendRectHeight = m_sendSizeHeight/2;

  cs::CvSink m_cvSink;
  cs::CvSource m_outputStream;

  
  
  double m_printX;
  DriveTrainSubsystemBase *m_pDriveObject = nullptr;
  
};
*/

//COMMENTED OUT FOR RESTART PURPOSES. THIS IS FOR REFERENCE.