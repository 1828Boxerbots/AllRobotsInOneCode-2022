/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/C418/ShooterSubsystemC418.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

ShooterSubsystemC418::ShooterSubsystemC418()
{
#ifndef NOHW
    Init();
    m_timer.Start();
    m_timer.Reset();
    m_shooterEncoder.Reset();
    m_startTime = m_timer.Get();
    m_encoderRawStart = m_shooterEncoder.GetRaw();
#endif
}

// This method will be called once per scheduler run
void ShooterSubsystemC418::Periodic()
{
    EncoderSpeed();
}

double ShooterSubsystemC418::EncoderSpeed()
{
#ifndef NOHW
    units::second_t difTime = m_timer.Get() - m_startTime;
    double difRaw = m_shooterEncoder.GetRaw() - m_encoderRawStart;
    //frc::SmartDashboard::PutNumber("C418 Shooter Time Dif", difTime);
    frc::SmartDashboard::PutNumber("C418 Shooter Raw Dif", difRaw);
    double speed = difRaw / (double)difTime;
    frc::SmartDashboard::PutNumber("C418 Shooter Speed", speed);
    frc::SmartDashboard::PutNumber("C418 Shooter Encoder", m_shooterEncoder.GetDistance());
    frc::SmartDashboard::PutNumber("C418 Shooter Encoder RAW", m_shooterEncoder.GetRaw());
    frc::SmartDashboard::PutNumber("C418 Shooter Encoder RATE", m_shooterEncoder.GetRate());
    m_encoderRawStart = m_shooterEncoder.GetRaw();
    m_startTime = m_timer.Get();
    return speed;
#else
    return 0;
#endif
}

void ShooterSubsystemC418::SetShootMotor(double speed)
{
#ifndef NOHW
    m_shooterMotor.Set(speed * m_motorSpeed);
    frc::SmartDashboard::PutNumber("C418 Shooter Encoder", m_shooterEncoder.GetDistance());
    frc::SmartDashboard::PutNumber("C418 Shooter Encoder RAW", m_shooterEncoder.GetRaw());
    frc::SmartDashboard::PutNumber("C418 Shooter Encoder RATE", m_shooterEncoder.GetRate());

#endif
}

void ShooterSubsystemC418::Init()
{
#ifndef NOHW
    m_shooterEncoder.Reset();
    m_shooterEncoder.SetDistancePerPulse(1 / PULSES_PER_ROTATION);
    m_shooterEncoder.SetReverseDirection(true);
    m_shooterMotor.SetInverted(true);
#endif
}

void ShooterSubsystemC418::ResetEncoder()
{
#ifndef NOHW
    m_shooterEncoder.Reset();
    frc::SmartDashboard::PutNumber("C418 Shooter Encoder", m_shooterEncoder.GetDistance());
    frc::SmartDashboard::PutNumber("C418 Shooter Encoder RAW", m_shooterEncoder.GetRaw());
    frc::SmartDashboard::PutNumber("C418 Shooter Encoder RATE", m_shooterEncoder.GetRate());
#endif
}
