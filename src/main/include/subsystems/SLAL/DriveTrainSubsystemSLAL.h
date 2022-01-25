/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/motorcontrol/Talon.h>
#include "../DriveTrainSubsystemBase.h"

class DriveTrainSubsystemSLAL : public DriveTrainSubsystemBase
{
public:
  DriveTrainSubsystemSLAL();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed);
  virtual void Init();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

private:
#ifndef NOHW
  frc::Talon m_leftMotor{PWM_LEFTMOTOR_SLAL};
  frc::Talon m_rightMotor{PWM_RIGHTMOTOR_SLAL};
#endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
