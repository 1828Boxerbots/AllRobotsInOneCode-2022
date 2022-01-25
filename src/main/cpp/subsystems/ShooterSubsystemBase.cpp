/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/ShooterSubsystemBase.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

ShooterSubsystemBase::ShooterSubsystemBase() {}

// This method will be called once per scheduler run
void ShooterSubsystemBase::Periodic() {}

void ShooterSubsystemBase::Shoot(double shootSpeed)
{
    //The shooter shouldn't be able to shoot backwards
    shootSpeed = -Util::Limit(shootSpeed);
    frc::SmartDashboard::PutNumber("Shoot Speed", shootSpeed);
    SetShootMotor(shootSpeed);
}

void ShooterSubsystemBase::ShootBump(bool bumpL, bool bumpR)
{
    if (bumpL == true && bumpR == false)
    {
        Shoot(-SHOOTSPEED);
    }
    else if (bumpL == false && bumpR == true)
    {
        Shoot(SHOOTSPEED);
    }
    else
    {
        Shoot(0.0);
    }
}

bool ShooterSubsystemBase::AtSetpoint(double position)
{
    return Util::CompareDouble(GetSetPoint(), position);
}

void ShooterSubsystemBase::DisableInit()
{
    SetShootMotor(0.0);
}
