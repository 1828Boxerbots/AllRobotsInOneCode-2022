/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/I2C.h>

#include "Util.h"

class LidarDriver
{
public:
  //Constructor
  LidarDriver(frc::I2C::Port port, int address);

  /* 
  *  Reads the raw distance from the Lidar.
  *  MUST BE CALLED AFTER INIT.
  */
  double GetDistanceInCM();

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

  // Utilizes a conversion factor to get Inches.
  double GetDistanceInInches();
  //double LidarDetectionSoftware(double detectionDistance);
private:
  /* 
  *  Required init function: Writes the command bit to the Lidar.
  *  This must be called or else you will not get any return from 
  *  the sensor.
  */
  void CommandInit();

  // Conversion Factor
  const double CM_TO_IN = 0.393701;

  // Default I2C Address
public:
  static const int LIDAR_ADDRESS = 0x62;

private:
  // Command Bit
  const int ACQ_COMMAND = 0x00;

  // Command Register
  const int ACQ_CONFIG_REG = 0x04;

  // Return Register
  const int STATUS = 0x01;

  // High Bit
  const int FULL_DELAY_HIGH = 0x0f;

  // Low Bit
  const int FULL_DELAY_LOW = 0x10;

  // I2C Object
  frc::I2C *m_pDevice = nullptr;
};

// 2/14/10
