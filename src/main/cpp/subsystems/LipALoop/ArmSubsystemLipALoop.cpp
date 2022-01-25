/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LipALoop/ArmSubsystemLipALoop.h"

ArmSubsystemLipALoop::ArmSubsystemLipALoop() {}

void ArmSubsystemLipALoop::Init()
{
    ResetToZero();
#ifndef NOHW
    m_armAngle = m_armServo.Get();
#endif
    frc::SmartDashboard::PutNumber("Arm Servo", m_armAngle);
}

void ArmSubsystemLipALoop::DisableInit()
{
    ResetToZero();
#ifndef NOHW
    m_armAngle = m_armServo.Get();
#endif
    frc::SmartDashboard::PutNumber("Arm Servo", m_armAngle);
}

void ArmSubsystemLipALoop::SetMotor(double angle)
{
    m_armAngle = angle;
#ifndef NOHW
    m_armServo.Set(m_armAngle);
#endif
    frc::SmartDashboard::PutNumber("Arm Servo", m_armAngle);
}

double ArmSubsystemLipALoop::GetMotor()
{
#ifndef NOHW
    m_armAngle = m_armServo.Get();
#endif
    return m_armAngle;
}

void ArmSubsystemLipALoop::LiftArmUp(double scale, double speed)
{
    m_armAngle += GetOneDegree() * GetScale();
    m_armAngle = Util::Limit(m_armAngle, GetMinLimit(), GetMaxLimit());
    SetMotor(m_armAngle);
}

void ArmSubsystemLipALoop::LiftArmDown(double scale, double speed)
{
    m_armAngle -= GetOneDegree() * GetScale();
    m_armAngle = Util::Limit(m_armAngle, GetMinLimit(), GetMaxLimit());
    SetMotor(m_armAngle);
}

void ArmSubsystemLipALoop::StopMotor()
{
    SetMotor(m_armAngle);
}

void ArmSubsystemLipALoop::ResetToZero()
{
#ifndef NOHW
    m_armServo.Set(0.0);
    m_armAngle = m_armServo.Get();
#else
    m_armAngle = 0.0;
#endif
    frc::SmartDashboard::PutNumber("Arm Servo", m_armAngle);
}

double ArmSubsystemLipALoop::GetOneDegree()
{
    return m_oneDegree;
}

double ArmSubsystemLipALoop::GetScale()
{
    return m_motorScale;
}

double ArmSubsystemLipALoop::GetMaxLimit()
{
    return ARM_MAX;
}

double ArmSubsystemLipALoop::GetMinLimit()
{
    return ARM_MIN;
}

int ArmSubsystemLipALoop::GetPosition()
{
#ifndef NOHW
    if (m_armServo.Get() == GetMaxLimit())
    {
        return HIGHEST_POS;
    }
    else if (m_armServo.Get() == GetMinLimit())
    {
        return LOWEST_POS;
    }
#endif
    return INVALID_POS;
}

void ArmSubsystemLipALoop::SetPosition(int pos)
{
#ifndef NOHW
    switch (pos)
    {
    case LOWEST_POS:
        m_armServo.Set(ARM_MIN);
        break;
    case HIGHEST_POS:
        m_armServo.Set(ARM_MAX);
        break;
    default:
        m_armServo.Set(ARM_MAX);
        break;
    }
#endif
}
