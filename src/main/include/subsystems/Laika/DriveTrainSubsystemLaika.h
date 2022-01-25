/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/motorcontrol/Spark.h>
#include "../DriveTrainSubsystemBase.h"

class DriveTrainSubsystemLaika : public DriveTrainSubsystemBase
{
public:
  DriveTrainSubsystemLaika();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed);
  virtual void Init();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

private:
#ifndef NOHW
  frc::Spark m_leftMotor{PWM_LEFTMOTOR_LAIKA};
  frc::Spark m_rightMotor{PWM_RIGHTMOTOR_LAIKA};
#endif
  double m_scale = .5;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
