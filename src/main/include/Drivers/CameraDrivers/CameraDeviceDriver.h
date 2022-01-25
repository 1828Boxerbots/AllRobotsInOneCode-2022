/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <cameraserver/CameraServer.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include "Util.h"

class CameraDeviceDriver {
 public:
  CameraDeviceDriver(int index);
  bool Init();
  void DisplayCamera();
  double WhereToTurn(double deadZone);

private:
  cv::Mat m_frame;
  cs::UsbCamera m_USBcamera;
  //cv::VideoCapture m_CVcamera;
  int m_index;
  double m_centroidX;
  double m_centroidY;
  double m_deadZone = 50.0;

  bool GetBlob();
  void SetColor();
};
