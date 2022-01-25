/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SLAL/DriveTrainSubsystemSLAL.h"

DriveTrainSubsystemSLAL::DriveTrainSubsystemSLAL() {}

void DriveTrainSubsystemSLAL::SetMotorL(double speed)
{
#ifndef NOHW
  m_leftMotor.Set(speed);
#endif
}

void DriveTrainSubsystemSLAL::SetMotorR(double speed)
{
#ifndef NOHW
  m_rightMotor.Set(speed);
#endif
}

void DriveTrainSubsystemSLAL::Init()
{
#ifndef NOHW
  m_leftMotor.SetInverted(true);
  m_rightMotor.SetInverted(false);
#endif
}
