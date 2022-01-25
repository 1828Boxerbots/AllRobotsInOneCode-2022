/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/MuxDrivers/MuxLidarDriver.h"

MuxLidarDriver::MuxLidarDriver(frc::I2C::Port i2cPort, int address, I2CMultiplexerDriver &breakout, uint8_t breakoutChannel) : m_breakout(breakout),
                                                                                                                               m_breakoutChannel(breakoutChannel)
{
    SetActive();
    m_lidar = new LidarDriver(i2cPort, address);
}

void MuxLidarDriver::SetActive()
{
    m_breakout.SetChannel(1 << (m_breakoutChannel));
}

double MuxLidarDriver::GetDistanceInCM()
{
    SetActive();
    return m_lidar->GetDistanceInCM();
}

double MuxLidarDriver::GetDistanceInInches()
{
    SetActive();
    return m_lidar->GetDistanceInInches();
}

bool MuxLidarDriver::StatusIsFatal()
{
    SetActive();
    //return m_lidar->StatusIsFatal();
}

// Completed 3/6/2020
