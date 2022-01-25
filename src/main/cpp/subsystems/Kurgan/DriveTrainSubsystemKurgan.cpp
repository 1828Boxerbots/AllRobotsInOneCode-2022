/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Kurgan/DriveTrainSubsystemKurgan.h"

DriveTrainSubsystemKurgan::DriveTrainSubsystemKurgan() {}

void DriveTrainSubsystemKurgan::SetMotorL(double speed)
{
#ifndef NOHW
  m_leftMotor1.Set(speed);
  m_leftMotor2.Set(speed);
#endif
}

void DriveTrainSubsystemKurgan::SetMotorR(double speed)
{
#ifndef NOHW
  m_rightMotor1.Set(speed);
  m_rightMotor2.Set(speed);
#endif
}

void DriveTrainSubsystemKurgan::Init()
{
#ifndef NOHW
  m_leftMotor1.SetInverted(false);
  m_leftMotor2.SetInverted(false);
  m_rightMotor1.SetInverted(true);
  m_rightMotor2.SetInverted(true);

  //bool isVision = m_cameraVision.Init();
  //Util::Log("isVision Working", isVision);
#endif
}

// double DriveTrainSubsystemKurgan::WhereToTurnVision(double deadZoneRange, double deadZone)
// {
//   return 0.0;
// }