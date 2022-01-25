/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Laika/DriveTrainSubsystemLaika.h"

DriveTrainSubsystemLaika::DriveTrainSubsystemLaika() {}

void DriveTrainSubsystemLaika::SetMotorL(double speed)
{
#ifndef NOHW
  m_leftMotor.Set(speed * m_scale);
#endif
}

void DriveTrainSubsystemLaika::SetMotorR(double speed)
{
#ifndef NOHW
  m_rightMotor.Set(speed * m_scale);
#endif
}

void DriveTrainSubsystemLaika::Init()
{
#ifndef NOHW
  m_leftMotor.SetInverted(false);
  m_rightMotor.SetInverted(true);
#endif
}