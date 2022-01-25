/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LipALoop/HandSubsystemLipALoop.h"

HandSubsystemLipALoop::HandSubsystemLipALoop() {}

// This method will be called once per scheduler run
void HandSubsystemLipALoop::Init()
{
    ResetToZero();
#ifndef NOHW
    m_handAngle = m_handServo.Get();
#endif
    frc::SmartDashboard::PutNumber("Arm Servo", m_handAngle);
}

void HandSubsystemLipALoop::HandMotor(double angle)
{
    m_handAngle = angle;
#ifndef NOHW
    m_handServo.Set(angle);
#endif
    frc::SmartDashboard::PutNumber("Hand Servo", m_handAngle);
}

void HandSubsystemLipALoop::MoveHandOpen()
{
    m_handAngle += GetOneDegree();
    m_handAngle = Util::Limit(m_handAngle, GetMinLimit(), GetMaxLimit());
    HandMotor(m_handAngle);
}

void HandSubsystemLipALoop::MoveHandClose()
{
    m_handAngle -= GetOneDegree();
    m_handAngle = Util::Limit(m_handAngle, GetMinLimit(), GetMaxLimit());
    HandMotor(m_handAngle);
}

void HandSubsystemLipALoop::MoveHandStop()
{
    HandMotor(m_handAngle);
}

void HandSubsystemLipALoop::ResetToZero()
{
#ifndef NOHW
    m_handServo.Set(0.0);
    m_handAngle = m_handServo.Get();
#else
    m_handAngle = 0.0;
#endif
    frc::SmartDashboard::PutNumber("Arm Servo", m_handAngle);
}

double HandSubsystemLipALoop::GetOneDegree()
{
    return m_oneDegree;
}

double HandSubsystemLipALoop::GetMinLimit()
{
    return HAND_MIN;
}

double HandSubsystemLipALoop::GetMaxLimit()
{
    return HAND_MAX;
}