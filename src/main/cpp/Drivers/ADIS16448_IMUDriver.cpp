/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/ADIS16448_IMUDriver.h"

ADIS16448_IMUDriver::ADIS16448_IMUDriver()
{
    m_pDevice = new frc::ADIS16448_IMU();
}

void ADIS16448_IMUDriver::IMUGyroInit(bool log)
{
    //Set Log "true" to show on smartdashboard that IMU is initialized
    if (log)
    {
        Util::Log("IMU Initialized", true, "IMU Driver");
    }
    ResetAngles();
    CalibrateIMU();
}

units::celsius_t ADIS16448_IMUDriver::GetTemperature()
{
    return m_pDevice->GetTemperature();
}

double ADIS16448_IMUDriver::GetPressure()
{
    return 0.0;
}

units::acceleration::meters_per_second_squared_t ADIS16448_IMUDriver::GetAccelX()
{
    return m_pDevice->GetAccelX();
}

/**
 * This returns the acceleration of the robot in the Y direction.
 */
units::acceleration::meters_per_second_squared_t ADIS16448_IMUDriver::GetAccelY()
{
    return m_pDevice->GetAccelY();
}

/**
 * This returns the acceleration of the robot in the Z direction.
 *
 * This axis is the default axis for gravitational acceleration.
 */
units::acceleration::meters_per_second_squared_t ADIS16448_IMUDriver::GetAccelZ()
{
    return m_pDevice->GetAccelZ();
}

/**
 * This returns the angle of the robot in the X direction.
 */
units::degree_t ADIS16448_IMUDriver::GetAngleX()
{
    return m_pDevice->GetGyroAngleX();
}

/**
 * This returns the angle of the robot in the Y direction.
 */
units::degree_t ADIS16448_IMUDriver::GetAngleY()
{
    return m_pDevice->GetGyroAngleY();
}

units::degree_t ADIS16448_IMUDriver::GetAngle()
{
    return m_pDevice->GetAngle();
}

units::degree_t ADIS16448_IMUDriver::GetCorrectAngleY()
{
    return ( GetAngleY() * M_CONVERSION_FACTOR );
}

units::degree_t ADIS16448_IMUDriver::GetCorrectAngleX()
{
    return ( GetAngleX() * M_CONVERSION_FACTOR );
}

units::degree_t ADIS16448_IMUDriver::GetCorrectAngleZ()
{
    return ( GetAngleZ() * M_CONVERSION_FACTOR );
}

/**
 * This returns the angle of the robot in the Z direction.
 */
units::degree_t ADIS16448_IMUDriver::GetAngleZ()
{
    return m_pDevice->GetGyroAngleZ();
}

/**
 * This grabs the magnetic influence in the X direction.
 */
units::tesla_t ADIS16448_IMUDriver::GetMagX()
{
    return m_pDevice->GetMagneticFieldX();
}

/**
 * This grabs the magnetic influence in the Y direction.
 */
units::tesla_t ADIS16448_IMUDriver::GetMagY()
{
    return m_pDevice->GetMagneticFieldY();
}

/**
 * This grabs the magnetic influence in the Z direction.
 */
units::tesla_t ADIS16448_IMUDriver::GetMagZ()
{
    return m_pDevice->GetMagneticFieldZ();
}

/**
 * This resets ALL angles of the IMU to a heading of 0. 
 * 
 * This is used in the IMU Init.
 */
void ADIS16448_IMUDriver::ResetAngles()
{
    m_pDevice->Reset();
}

/**
 * This is used exclusively by the IMU Init.
 * 
 * This is not the same as ResetAngles(); This makes sure the IMU reads angles properly.
 */
void ADIS16448_IMUDriver::CalibrateIMU()
{
    m_pDevice->Calibrate();
}

/**
 * This function is designed to show you all of the sensor outputs of the IMU.
 * 
 * 3-Axis Angles, Accelerations, and Magnetic pulls, as well as temperature and pressure.
 */
void ADIS16448_IMUDriver::LogAllValues()
{
    // Util::Log("Angle X", GetAngleX(), "IMU DRIVER");
    // Util::Log("Angle Y", GetAngleY(), "IMU DRIVER");
    // Util::Log("Angle Z", GetAngleZ(), "IMU DRIVER");
    // Util::Log("Magnetic Instant X", GetMagX(), "IMU DRIVER");
    // Util::Log("Magnetic Instant Y", GetMagY(), "IMU DRIVER");
    // Util::Log("Magnetic Instant Z", GetMagZ(), "IMU DRIVER");
    // Util::Log("Acceleration X", GetAccelX(), "IMU DRIVER");
    // Util::Log("Acceleration Y", GetAccelY(), "IMU DRIVER");
    // Util::Log("Acceleration Z", GetAccelZ(), "IMU DRIVER");
    // Util::Log("Temperature", GetTemperature(), "IMU DRIVER");
    // Util::Log("Pressure", GetPressure(), "IMU DRIVER");
}

// Completed 3/4/2020
