/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/LidarDriver.h"

LidarDriver::LidarDriver(frc::I2C::Port port, int address)
{
    m_pDevice = new frc::I2C(port, address);
}

void LidarDriver::CommandInit()
{
    m_pDevice->Write(ACQ_COMMAND, ACQ_CONFIG_REG);
}

double LidarDriver::GetDistanceInCM()
{
    CommandInit();

    uint8_t val;
    while (m_pDevice->Read(STATUS, 1, &val) == false)
    {
        if ((val & 0x1) == 0)
        {
            break;
        }
    }

    uint8_t high;
    uint8_t low;
    m_pDevice->Read(FULL_DELAY_HIGH, 1, &high);
    m_pDevice->Read(FULL_DELAY_LOW, 1, &low);
    uint16_t centimeters = (high << 8) | low;
    uint16_t centimeters2 = (low << 8) | high; 
    // Use this if you want to see distance on Smashboard
    
    // Util::Log("Lidar High", high, "LidarDriver");

    // Util::Log("Lidar Low", low, "LidarDriver");

    Util::Log("Lidar Distance", centimeters, "LidarDriver");

    // Util::Log("Lidar Distance 2", centimeters2, "LidarDriver");

    return (double)centimeters;
}

double LidarDriver::GetDistanceInInches()
{
    return GetDistanceInCM() * CM_TO_IN;
}

/*double LidarDriver::LidarDetectionSoftware(double detectionDistance)
{
    double currentDetection = GetDistanceInInches();
    double startDetection = GetDistanceInInches();
    bool tooClose = false;
    Util::Log("DistanceDetection", false, "LidarDriver");
    while(currentDetection - startDetection < detectionDistance)
    {
        if(currentDetection - startDetection > detectionDistance)
        {
            Util::Log("DistanceDetection", true, "LidarDriver");
            tooClose = true;
        }
    }
}
*/
