/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/ADXRS450_Gyro.h>

#include "Util.h"

class ADXRS_450GyroDriver
{
public:
  ADXRS_450GyroDriver(frc::SPI::Port port);

  /** 
   * Initializes the Gyro
   * 
   * @param log: put true if you want to see if the gyro has been initialized
  */
  void GyroInit(bool log = false);

  // Resets the Gyro to a heading of 0 degrees
  void Reset();

  // Makes sure the Gyro initializes correctly
  void Calibrate();

  // In Degrees
  double GetAngle();

  // In Degrees per Second
  double GetRate();

  // States whether or not the sensor is compromised
  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
  frc::ADXRS450_Gyro *m_pDevice = nullptr;
};

// 2/14/20
