/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/HallEffectOmnipolarDriver.h"

HallEffectOmnipolarDriver::HallEffectOmnipolarDriver(int port)
{
    m_pDevice = new frc::DigitalInput(port);
}

bool HallEffectOmnipolarDriver::Get()
{
    return m_pDevice->Get();
}

// 2/15/20
