/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//#include "rev/ColorSensorV3.h"
#include "../../subsystems/SpinSubsystemBase.h"
#include "../I2CMultiplexerDriver.h"

class MuxColorSensorDriver
{
public:
  MuxColorSensorDriver(frc::I2C::Port i2cPort, I2CMultiplexerDriver &breakout, uint8_t breakoutChannel);

  void SetActive();
  SpinSubsystemBase::FMSColors GetColor();
  std::string GetColorString();

  bool IsRed(double R, double G, double B);
  bool IsGreen(double R, double G, double B);
  bool IsBlue(double R, double G, double B);
  bool IsYellow(double R, double G, double B);
  bool StatusIsFatal();

  void ReturnAllColors();
  void DetectOverlap();

private:
  void DetectTripleOverlap(bool isRed, bool isBlue, bool isGreen, bool isYellow);

  // The multiplexer "object"
  I2CMultiplexerDriver &m_breakout;

  // The channel that t?
  uint8_t m_breakoutChannel;

  //
  //rev::ColorSensorV3 *m_pColorSensor = nullptr;
  
  // The file location, for telemetry purposes
  const char *m_fileLoc = "ColorSensorDriver.cpp";
};

// Completed 3/3/2020 , untested
