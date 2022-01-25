/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/C418/LoaderSubsystemC418.h"
#include "../include/Util.h"

LoaderSubsystemC418::LoaderSubsystemC418() {}

// This method will be called once per scheduler run
void LoaderSubsystemC418::Periodic()
{
#ifndef NOHW
    Util::Log("Load Photogate", m_photogate.Get());
    if (m_photogate.Get())
    {
        m_spike.TurnSpikeOn();
    }
    else
    {
        m_spike.TurnSpikeOff();
    }
#endif
}

void LoaderSubsystemC418::SetLoadMotor(double speed, int motorNumber)
{
#ifndef NOHW
    Util::Log("MotorSpeed", speed, GetName());
    Util::Log("Motor Number", motorNumber, GetName());
    switch (motorNumber)
    {
    case MOTOR_TOP:
        m_loaderMotorTop.Set(speed);
        break;

    case MOTOR_BOTTOM:
        m_loaderMotorBottom.Set(speed);
        break;

    case MOTOR_INTAKE:
        m_loaderMotorIntake.Set(speed);
        break;

    case MOTOR_INTAKE_AND_BOTTOM:
        m_loaderMotorIntake.Set(speed);
        m_loaderMotorBottom.Set(speed);
        break;
    
    case MOTOR_BOTTOM_AND_TOP:
        m_loaderMotorTop.Set(speed);
        m_loaderMotorBottom.Set(speed);
        break;
        
    default:
        m_loaderMotorTop.Set(speed);
        m_loaderMotorIntake.Set(speed);
        m_loaderMotorBottom.Set(speed);

        Util::Log("TopLoader", m_loaderMotorTop.Get());
        Util::Log("IntakeLoader", m_loaderMotorIntake.Get());
        Util::Log("BottomLoader", m_loaderMotorBottom.Get());
        break;
    }
#endif
}

void LoaderSubsystemC418::PhotogateStop(double speed)
{
    frc::Timer timer;
//Continue spining motor until photogate is set.
#ifndef NOHW
    timer.Start();
    while (m_photogate.Get() == true)
    {
        SetLoadMotor(speed);

        if(timer.Get() >= 10_s)
        {
            break;
        }
    }
    timer.Stop();
    SetLoadMotor(0.0);
    SetLoadMotor(0.0, MOTOR_BOTTOM);
#endif
}

//Checks to see if the ball is loaded
bool LoaderSubsystemC418::IsLoaded()
{
//returns the vail of the photogate
#ifndef NOHW
    return m_photogate.Get();
#else
    return 0;
#endif
}

void LoaderSubsystemC418::Init()
{
#ifndef NOHW
    m_loaderMotorTop.SetInverted(false);
    m_loaderMotorIntake.SetInverted(false);
    m_loaderMotorBottom.SetInverted(true);
#endif
}
