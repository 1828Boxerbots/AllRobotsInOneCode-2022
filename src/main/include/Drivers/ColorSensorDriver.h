/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//#include "rev/ColorSensorv3.h"
#include "Constants.h"
#include "../subsystems/SpinSubsystemBase.h"
#include "Util.h"

class ColorSensorDriver
{
public:
  ColorSensorDriver(frc::I2C::Port port);

  void Init() {}

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

  // Function designed to give you an FMSColor (Specific to C418)
  SpinSubsystemBase::FMSColors GetColor();

  // Function designed to return Red, Yellow, Green, or Blue as a string.
  // Returns Invalid if the color is not R-G-B-Y, and ERROR if there is no color being sent at all.
  std::string GetColorString();

  // Utilizes the Color Sensor's built-in proximity sensor.
  uint32_t GetProximity();

  /**
   * These functions are used in GetColor.
   */
  static bool IsRed(double R, double G, double B);
  static bool IsGreen(double R, double G, double B);
  static bool IsBlue(double R, double G, double B);
  static bool IsYellow(double R, double G, double B);

  void ReturnAllColors();

  // Debug function used to determine whether or not a color returns 2 or more different colors.
  void DetectOverlap();

private:
  // Private because it's integrated into DetectOverlap only. Easiest and fastest to use direct integration.
  void DetectTripleOverlap(bool isRed, bool isBlue, bool isGreen, bool isYellow, const char *fileLoc);

  //rev::ColorSensorV3 *m_pDevice = nullptr;
};

// 3/5/2020
