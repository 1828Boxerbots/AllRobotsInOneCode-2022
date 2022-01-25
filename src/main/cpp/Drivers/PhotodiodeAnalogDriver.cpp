/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/PhotodiodeAnalogDriver.h"

PhotodiodeAnalogDriver::PhotodiodeAnalogDriver(int port)
{
    m_pDevice = new frc::AnalogInput(port);
}

double PhotodiodeAnalogDriver::Get()
{
    return m_pDevice->GetVoltage();
}
