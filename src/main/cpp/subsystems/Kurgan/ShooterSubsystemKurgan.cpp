/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/Kurgan/ShooterSubsystemKurgan.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

ShooterSubsystemKurgan::ShooterSubsystemKurgan() {}

// This method will be called once per scheduler run

void ShooterSubsystemKurgan::SetShootMotor(double speed)
{
#ifndef NOHW
    m_shootOne.Set(-speed);
    m_shootTwo.Set(-speed);
    m_shootThree.Set(-speed);
    m_shootFour.Set(-speed);
#endif
}
