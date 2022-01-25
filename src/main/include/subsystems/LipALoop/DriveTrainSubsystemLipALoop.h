/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/motorcontrol/Victor.h>
#include "../DriveTrainSubsystemBase.h"

class DriveTrainSubsystemLipALoop : public DriveTrainSubsystemBase
{
public:
  DriveTrainSubsystemLipALoop();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed);
  virtual void Init();

private:
#ifndef NOHW
  frc::Victor m_leftMotor{PWM_LEFTMOTOR_LIPALOOP};
  frc::Victor m_rightMotor{PWM_RIGHTMOTOR_LIPALOOP};
#endif
  double m_scaleL = 0.3;
  double m_scaleR = 0.3;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
