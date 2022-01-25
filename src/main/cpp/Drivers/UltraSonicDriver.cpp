/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/UltrasonicDriver.h"

UltrasonicDriver::UltrasonicDriver(int port)
{
    m_pDevice = new frc::AnalogInput(port);
}

// Returns distance in centimeters by grabbing raw values and scaling them.
double UltrasonicDriver::GetDistanceInCM()
{
    return (m_pDevice->GetVoltage() * m_calibration);
}

// Returns distance in inches by converting from centimeters.
double UltrasonicDriver::GetDistanceInInch()
{
    return ( GetDistanceInCM() * CM_TO_IN );
}

// 2/15/2021
