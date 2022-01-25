/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../include/subsystems/SpinSubsystemBase.h"
#include "Constants.h"
#include <frc/motorcontrol/Victor.h>
#include <frc/Encoder.h>
#include <frc/I2C.h>
#include "../../Drivers/MuxDrivers/MuxColorSensorDriver.h"
#include "../../Drivers/I2CMultiplexerDriver.h"

class SpinSubsystemC418 : public SpinSubsystemBase
{
public:
  SpinSubsystemC418(I2CMultiplexerDriver *pMultiplexerDriver);

  void Periodic() override;

  void Init() override;
  void SetSpinMotor(double speed = 1.0) override;
  double GetTicksPerRevolution() override;
  void SpinNumRotations(double speed = 1.0, int wantedRotation = 7) override;
  void SpinToColor(double speed = 1.0) override;
  std::string GetColor() override;
  FMSColors ReadColorSensor() override;

private:
  FMSColors GetFMSColor();
  int CalcDir();
  FMSColors ConvertColor(FMSColors color);

#ifndef NOHW
  frc::Victor m_spinMotor{PWM_SPINNERMOTOR_C418};

  I2CMultiplexerDriver *m_pMultiplexerDiver = nullptr;

#ifdef M_COLOR
  MuxColorSensorDriver *m_pColorSensor = nullptr; // Paramaters: {I2C_PORT_MULTIPLEXER_C418, m_multiplexer, U8T_LINE_COLORSENSOR_C418};
#endif
#endif

  double m_scale = 0.5;

  int m_beatColorRead = 0;
};
