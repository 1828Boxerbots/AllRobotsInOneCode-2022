/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../I2CMultiplexerDriver.h"
#include "../LidarDriver.h"

class MuxLidarDriver
{
public:
  MuxLidarDriver(frc::I2C::Port i2cPort, int address, I2CMultiplexerDriver &breakout, uint8_t breakoutChannel);
  void SetActive();
  double GetDistanceInCM();
  double GetDistanceInInches();
  bool StatusIsFatal();

private:
  I2CMultiplexerDriver &m_breakout;
  uint8_t m_breakoutChannel;
  LidarDriver *m_lidar;
};
