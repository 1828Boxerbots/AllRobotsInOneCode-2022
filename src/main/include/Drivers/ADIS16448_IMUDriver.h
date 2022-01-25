/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//#include <adi/ADIS16448_imu.h>
#include <frc/ADIS16448_imu.h>

#include "Util.h"

class ADIS16448_IMUDriver
{
public:
  ADIS16448_IMUDriver();

  void IMUGyroInit(bool log = false);

  units::celsius_t GetTemperature();
  double GetPressure();
  units::acceleration::meters_per_second_squared_t GetAccelX();
  units::acceleration::meters_per_second_squared_t GetAccelY();
  units::acceleration::meters_per_second_squared_t GetAccelZ();
  units::degree_t GetAngleX();
  units::degree_t GetAngleY();
  units::degree_t GetCorrectAngleY();
  units::degree_t GetCorrectAngleX();
  units::degree_t GetCorrectAngleZ();
  units::degree_t GetAngleZ();
  units::degree_t GetAngle();
  units::tesla_t GetMagX();
  units::tesla_t GetMagY();
  units::tesla_t GetMagZ();

  void ResetAngles();
  void CalibrateIMU();
  void LogAllValues();

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
  // The IMU sensor object
  frc::ADIS16448_IMU *m_pDevice = nullptr;

  double M_CONVERSION_FACTOR = ( 180 / Util::PI );
};

// 3/4/2020 Completed, Untested
