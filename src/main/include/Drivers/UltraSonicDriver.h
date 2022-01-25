/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/AnalogInput.h>

class UltrasonicDriver
{
public:
  UltrasonicDriver(int port);

  double GetDistanceInCM();
  double GetDistanceInInch();

  // Every Ultrasonic sensor has its own calibration factor, use this to select the correct one.
  void SetCalibration(double value) { m_calibration = value; }

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
  frc::AnalogInput *m_pDevice = nullptr;
  const double CM_TO_IN = 0.393701;
  double m_calibration = 1.0;
};

// 2/15/2021
