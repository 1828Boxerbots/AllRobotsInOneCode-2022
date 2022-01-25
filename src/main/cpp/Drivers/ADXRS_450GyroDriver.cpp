/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/ADXRS_450GyroDriver.h"

ADXRS_450GyroDriver::ADXRS_450GyroDriver(frc::SPI::Port port)
{
    m_pDevice = new frc::ADXRS450_Gyro(port);
}

void ADXRS_450GyroDriver::Reset()
{
    m_pDevice->Reset();
}

void ADXRS_450GyroDriver::Calibrate()
{
    m_pDevice->Calibrate();
}

void ADXRS_450GyroDriver::GyroInit(bool log)
{
    if (log)
    {
        Util::Log("Initialized Gyro", true, "ADXRS450_GYRO DRIVER");
    }
    Reset();
    Calibrate();
}

double ADXRS_450GyroDriver::GetAngle()
{
    return m_pDevice->GetAngle();
}

double ADXRS_450GyroDriver::GetRate()
{
    return m_pDevice->GetRate();
}

// 3/4/2020
