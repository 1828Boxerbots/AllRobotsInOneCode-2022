/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/LoaderSubsystemBase.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

LoaderSubsystemBase::LoaderSubsystemBase() {}

// This method will be called once per scheduler run
void LoaderSubsystemBase::Periodic() {}

void LoaderSubsystemBase::LoadMotor(double loadSpeed)
{
    loadSpeed = Util::Limit(loadSpeed);
    loadSpeed = loadSpeed * m_scale;
    frc::SmartDashboard::PutNumber("Load Speed", loadSpeed);
    SetLoadMotor(loadSpeed);
}

void LoaderSubsystemBase::Load(double loadSpeed, double ejectSpeed)
{
    frc::SmartDashboard::PutNumber("Load Speed", loadSpeed);
    frc::SmartDashboard::PutNumber("Eject Speed", ejectSpeed);

    if (loadSpeed > 0.1 && ejectSpeed < 0.1)
    {
        LoadMotor(loadSpeed);
        frc::SmartDashboard::PutBoolean("Running Motor", true);
    }
    else if (loadSpeed < 0.1 && ejectSpeed > 0.1)
    {
        LoadMotor(-ejectSpeed);
        frc::SmartDashboard::PutBoolean("Running Motor", true);
    }
    else
    {
        frc::SmartDashboard::PutBoolean("Running Motor", false);
    }
}

void LoaderSubsystemBase::LoadXY(bool xButton, bool yButton)
{
    if (xButton == true && yButton == false)
    {
        LoadMotor(EJECTSPEED);
    }
    else if (xButton == false && yButton == true)
    {
        LoadMotor(LOADSPEED);
    }
    else
    {
        LoadMotor(0.0);
    }
}
