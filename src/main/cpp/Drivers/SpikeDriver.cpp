/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/SpikeDriver.h"

SpikeDriver::SpikeDriver(int port)
{
    m_pDevice = new frc::Relay(port);
}

// Sets the Relay to the "On" position.
void SpikeDriver::TurnSpikeOn()
{
    m_pDevice->Set(frc::Relay::Value::kForward);
}

// Sets the Relay to the "Off" position.
void SpikeDriver::TurnSpikeOff()
{
    m_pDevice->Set(frc::Relay::Value::kOff);
}

frc::Relay::Value SpikeDriver::GetState()
{
    return m_pDevice->Get();
}

// 2/18/2020
