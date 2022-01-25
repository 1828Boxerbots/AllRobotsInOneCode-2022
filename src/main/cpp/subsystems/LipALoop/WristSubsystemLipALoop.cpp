/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LipALoop/WristSubsystemLipALoop.h"

WristSubsystemLipALoop::WristSubsystemLipALoop() {}

void WristSubsystemLipALoop::Init()
{
    ResetToZero();
#ifndef NOHW
    m_wristAngle = m_wristServo.Get();
#endif
    frc::SmartDashboard::PutNumber("Wrist Servo", m_wristAngle);
}

void WristSubsystemLipALoop::WristMotor(double angle)
{
    m_wristAngle = angle;
#ifndef NOHW
    m_wristServo.Set(angle);
#endif
    frc::SmartDashboard::PutNumber("Wrist Servo", m_wristAngle);
}

void WristSubsystemLipALoop::MoveWristUp()
{
    m_wristAngle += GetOneDegree();
    m_wristAngle = Util::Limit(m_wristAngle, WRIST_MIN, WRIST_MAX);
    WristMotor(m_wristAngle);
}

void WristSubsystemLipALoop::MoveWristDown()
{
    m_wristAngle -= GetOneDegree();
    m_wristAngle = Util::Limit(m_wristAngle, WRIST_MIN, WRIST_MAX);
    WristMotor(m_wristAngle);
}

void WristSubsystemLipALoop::MoveWristStop()
{
    WristMotor(m_wristAngle);
}

void WristSubsystemLipALoop::ResetToZero()
{
#ifndef NOHW
    m_wristServo.Set(0.0);
    m_wristAngle = m_wristServo.Get();
#else
    m_wristAngle = 0.0;
#endif
    frc::SmartDashboard::PutNumber("Wrist Servo", m_wristAngle);
}

double WristSubsystemLipALoop::GetOneDegree()
{
    return m_oneDegree;
}

double WristSubsystemLipALoop::GetMinLimit()
{
    return WRIST_MIN;
}

double WristSubsystemLipALoop::GetMaxLimit()
{
    return WRIST_MAX;
}

// 3/6/2020
