/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/C418/SpinSubsystemC418.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../../../include/RobotContainer/RobotContainerC418.h"
#include "../../../include/subsystems/C418/ArmSubsystemC418.h"
#include "../../../include/subsystems/ArmSubsystemBase.h"

SpinSubsystemC418::SpinSubsystemC418(I2CMultiplexerDriver *pMultiplexerDriver)
{
    m_pMultiplexerDiver = pMultiplexerDriver;

#ifdef M_COLOR
    m_pColorSensor = new MuxColorSensorDriver(I2C_PORT_MULTIPLEXER_C418, *pMultiplexerDriver, U8T_LINE_COLORSENSOR_C418);
#endif
}

void SpinSubsystemC418::Init()
{
}

void SpinSubsystemC418::Periodic()
{
#ifdef M_COLOR
    m_pColorSensor->ReturnAllColors();
    m_pColorSensor->GetColor();
    m_pColorSensor->DetectOverlap();
    Util::Log("Count Color Read", m_beatColorRead++, "spinC418");
#endif
}

void SpinSubsystemC418::SetSpinMotor(double speed)
{
#ifndef NOHW
    m_spinMotor.Set(speed * m_scale);
#endif
}

//SpinNumRotations is where it spins the Control Panel a certain number of times.
void SpinSubsystemC418::SpinNumRotations(double speed, int wantedRotation)
{

#ifdef M_COLOR
    //Gets the starting color of the wheel
    FMSColors startColor = m_pColorSensor->GetColor();

    //Checks if it picked up a valid color
    if (startColor == INVALID)
    {
        return;
    }

    //Start Spinning if color is valid
    SetSpinMotor(speed);

    //Declares the currentColor Variable
    FMSColors currentColor;

    for (int halfRotations = 0; halfRotations < wantedRotation; halfRotations++)
    {
        //Do-While loop till we are out of the starting color
        do
        {
            currentColor = m_pColorSensor->GetColor();
        } while (currentColor == startColor);

        /**Starts after we leave the start color
        * Do-While loop till we see the start color again
        */
        do
        {
            currentColor = m_pColorSensor->GetColor();
        } while (currentColor != startColor);
    }

    //Stops the Spinner after finished spinning
    Stop();
#endif
}

SpinSubsystemBase::FMSColors SpinSubsystemC418::ReadColorSensor()
{
#ifdef M_COLOR
    return m_pColorSensor->GetColor();
#else
    return INVALID;
#endif
}

double SpinSubsystemC418::GetTicksPerRevolution()
{
    return 360;
}

std::string SpinSubsystemC418::GetColor()
{
#ifdef M_COLOR
    m_pColorSensor->ReturnAllColors();
    return m_pColorSensor->GetColorString();
#else
    return NULL;
#endif
}

//SpinToColor spins the Control Panel to where the mapped color is a certain color.
void SpinSubsystemC418::SpinToColor(double speed)
{

    FMSColors wantedColor = RobotContainerC418::givenColor;
    FMSColors realColor;

    if (ReadColorSensor() == INVALID)
    {
        return;
    }

    do
    {
        FMSColors currentColor = ReadColorSensor();

        currentColor = MapColors(currentColor);
        realColor = currentColor;

        SetSpinMotor(speed);
    } while (realColor != wantedColor);

    Stop();
}

SpinSubsystemBase::FMSColors SpinSubsystemC418::GetFMSColor()
{
    //tbt
    return FMSColors::RED;
}

SpinSubsystemBase::FMSColors SpinSubsystemC418::ConvertColor(FMSColors color)
{
    switch (color)
    {
    case RED:
        return BLUE;
        break;

    case BLUE:
        return RED;
        break;

    case YELLOW:
        return GREEN;
        break;

    case GREEN:
        return YELLOW;
        break;

    default:
        return INVALID;
        break;
    }
}

int SpinSubsystemC418::CalcDir()
{
    /*
    0 = dont move
    1 = Clock-wise TBD
    -1 = Counter Clock-wise TBD
    -2 = Invalid conditions
    */

    FMSColors wantedColor = GetFMSColor();
    FMSColors currentColor = ReadColorSensor();

    int direction = -2;

    switch (wantedColor)
    {
    case RED:
        if (currentColor == YELLOW || currentColor == BLUE)
        {
            direction = 1;
        }
        else if (currentColor == GREEN)
        {
            direction = -1;
        }
        else if (currentColor == RED)
        {
            direction = 0;
        }
        break;

    case GREEN:
        if (currentColor == YELLOW || currentColor == BLUE)
        {
            direction = 1;
        }
        else if (currentColor == RED)
        {
            direction = -1;
        }
        else if (currentColor == GREEN)
        {
            direction = 0;
        }
        break;

    case YELLOW:
        if (currentColor == GREEN || currentColor == BLUE)
        {
            direction = 1;
        }
        else if (currentColor == RED)
        {
            direction = -1;
        }
        else if (currentColor == YELLOW)
        {
            direction = 0;
        }
        break;

    case BLUE:
        if (currentColor == GREEN || currentColor == RED)
        {
            direction = 1;
        }
        else if (currentColor == YELLOW)
        {
            direction = -1;
        }
        else if (currentColor == BLUE)
        {
            direction = 0;
        }
        break;

    default:
        direction = 0;
        break;
    }

    return direction;
}
