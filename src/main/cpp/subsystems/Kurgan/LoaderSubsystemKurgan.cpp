/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/Kurgan/LoaderSubsystemKurgan.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

LoaderSubsystemKurgan::LoaderSubsystemKurgan() {}

// This method will be called once per scheduler run

void LoaderSubsystemKurgan::SetLoadMotor(double speed, int motorNumber)
{
#ifndef NOHW
    m_loaderMotor.Set(speed);
#endif
}
