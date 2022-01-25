/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ArmSubsystemBase.h"

ArmSubsystemBase::ArmSubsystemBase() {}

// This method will be called once per scheduler run

//
//LiftSubsystem
//

void ArmSubsystemBase::Lift(double armSpeed)
{
    armSpeed = Util::Limit(armSpeed);
    frc::SmartDashboard::PutNumber("Lift Power", armSpeed);
    SetMotor(armSpeed);
}

void ArmSubsystemBase::Log(std::string title, double num)
{
    frc::SmartDashboard::PutNumber("Arm " + title, num);
}

void ArmSubsystemBase::Log(std::string title, int num)
{
    frc::SmartDashboard::PutNumber("Arm " + title, num);
}

void ArmSubsystemBase::Log(std::string title, bool flag)
{
    frc::SmartDashboard::PutBoolean("Arm " + title, flag);
}

void ArmSubsystemBase::Log(std::string title, std::string phrase)
{
    frc::SmartDashboard::PutString("Arm " + title, phrase);
}