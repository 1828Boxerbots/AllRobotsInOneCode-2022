/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/Rocky/LoaderSubsystemRocky.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

LoaderSubsystemRocky::LoaderSubsystemRocky() {}

// This method will be called once per scheduler run

void LoaderSubsystemRocky::SetLoadMotor(double speed, int motorNumber)
{
#ifndef NOHW
    m_loaderMotor.Set(speed);
#endif
}
bool LoaderSubsystemRocky::AutoLoaderRunTime()
{
    bool loaderComplete = false;
    units::second_t loaderTime = 2_s;
    Util::DelayInSeconds(loaderTime);
    return loaderComplete = true;
}
void LoaderSubsystemRocky::WaitLoader(double waitTime)
{
    Util::DelayInSeconds((units::second_t)waitTime);
}