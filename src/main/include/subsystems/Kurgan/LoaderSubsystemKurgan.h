/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/motorcontrol/Victor.h>
#include "../LoaderSubsystemBase.h"

class LoaderSubsystemKurgan : public LoaderSubsystemBase
{
public:
  LoaderSubsystemKurgan();

  void SetLoadMotor(double speed = 1.0, int motorNumber = -1) override;

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

private:
#ifndef NOHW
  frc::Victor m_loaderMotor{PWM_LOADMOTOR_KURGAN};
#endif

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
