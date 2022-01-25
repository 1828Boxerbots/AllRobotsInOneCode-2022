/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

class SpinSubsystemBase : public frc2::SubsystemBase
{
public:
  SpinSubsystemBase();

  static constexpr double COLORWHEELRADIUS = 16.0;  //inches
  static constexpr double SPINWHEELRADIUS = 2.0;    //inches
  static constexpr double DEFAULTREVOLUTIONS = 4.0; //Revolutions

  enum FMSColors
  {
    INVALID = -1,
    RED,
    GREEN,
    BLUE,
    YELLOW
  };

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();
  std::string FMStoString(FMSColors color);
  void SpinWithEncoders(double targetRadius = COLORWHEELRADIUS, double ourRadius = SPINWHEELRADIUS, double revolutions = DEFAULTREVOLUTIONS);
  virtual void SpinNumRotations(double speed = 1.0, int wantedRotation = 1) {}
  void SpinUntilColor(FMSColors targetColor = INVALID);
  FMSColors MapColors(FMSColors color);
  virtual void InterpretFMS(std::string rawColor);
  virtual void Init() {}
  virtual FMSColors ReadColorSensor() { return m_color; };
  virtual void SetSpinMotor(double speed = 1.0) {}
  void Stop() { SetSpinMotor(0.0); }
  virtual double GetNumberOfTicks(double targetRadius, double revolutions, double ourRadius); //inches
  virtual double GetEncoderTicks() { return m_encoder++; }
  virtual double GetTicksPerRevolution() { return 256; }
  virtual std::string GetColor() { return "NULL"; }
  virtual void SpinToColor(double speed = 1.0) {}
  void Log();

protected:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  double m_encoder = 1;

  FMSColors m_colorTest;

  FMSColors m_color = INVALID;
};
