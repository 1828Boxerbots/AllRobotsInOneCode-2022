/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/I2CMultiplexerDriver.h"

/**
 *  This is the constructor. It creates an i2c device and initializes the current channel to zero.
 */
I2CMultiplexerDriver::I2CMultiplexerDriver(frc::I2C::Port i2cPort, int breakoutAddress)
{
    m_pDevice = new frc::I2C(i2cPort, breakoutAddress);
    m_current_channel = 0;
}

// Communicate which channel the mux should be on
//          [x,x,x,x,x,x,x,x]
// channel   7,6,5,4,3,2,1,0
//
// Returns whether or not the channel changed.
bool I2CMultiplexerDriver::SetChannel(uint8_t channel, bool log)
{
    // This statement does not run if the current channel already matches the one sent.
    // Thus, you can spam the mux with SetChannel just to make sure it's looking at the right sensor.
    if (m_current_channel != channel)
    {
        // Switches the channel in the code
        m_current_channel = channel;

        // Command to the multiplexer to change which sensor to look at
        bool retVal = m_pDevice->WriteBulk(&channel, 1);

        if (retVal)
        {
            //Util::SendErrorAndCode("Write to Mux failed!", 151, "I2CMultiplexerDriver.cpp");
            return false; // False because channel didn't change, mux write failed
        }

        if (log)
        {
            Util::Log("Current Mux Channel", GetChannelName(m_current_channel), "Mux Driver");
            Util::Log("Raw Channel", m_current_channel, "Mux Driver");
        }

        return true; // True because the channel has changed
    }

    // log is defaulted to true.
    // This is just a telemetry thing to show which sensor the mux is looking at.
    if (log)
    {
        Util::Log("Current Mux Channel", GetChannelName(m_current_channel), "Mux Driver");
        Util::Log("Raw Channel", m_current_channel, "Mux Driver");
    }
    return false; // Channel has not changed because the channel was already set
}

/**
 * Function for other files to see which channel the mux is on (number)
 */
uint8_t I2CMultiplexerDriver::GetChannel()
{
    return m_current_channel;
}

/**
 * Function for other files to see which channel the mux is on (name)
 * Also great for telemetry purposes.
 */
std::string I2CMultiplexerDriver::GetChannelName(uint8_t channel)
{
    std::string name = "Invalid";

    //Not Shifted
    /*if (channel == (U8T_LINE_COLORSENSOR_C418))         {name = "Color Sensor";}
    #ifdef M_DISTANCE
    if (channel == (U8T_LINE_LEFTDISTANCESENSOR_C418))  {name = "Left Distance Sensor";}
    if (channel == (U8T_LINE_RIGHTDISTANCESENSOR_C418)) {name = "Right Distance Sensor";}
    #endif
    if (channel == (U8T_LINE_LIDAR_C418))               {name = "Lidar";}

    //Shifted and -1
    if (channel == (1 << (U8T_LINE_COLORSENSOR_C418 -1 )))         {name = "Color Sensor";}
    #ifdef M_DISTANCE
    if (channel == (1 << (U8T_LINE_LEFTDISTANCESENSOR_C418 -1 )))  {name = "Left Distance Sensor";}
    if (channel == (1 << (U8T_LINE_RIGHTDISTANCESENSOR_C418 -1 ))) {name = "Right Distance Sensor";}
    #endif
    if (channel == (1 << (U8T_LINE_LIDAR_C418 -1 )))               {name = "Lidar";}*/

    //Shifted
    if (channel == (1 << U8T_LINE_COLORSENSOR_C418))
    {
        name = "Color Sensor";
    }
    if (channel == (1 << U8T_LINE_LEFTDISTANCESENSOR_C418))
    {
        name = "Left Distance Sensor";
    }
    if (channel == (1 << U8T_LINE_RIGHTDISTANCESENSOR_C418))
    {
        name = "Right Distance Sensor";
    }
    if (channel == (1 << U8T_LINE_LIDAR_C418))
    {
        name = "Lidar";
    }

    //Shifted and +1

    /*
    if (channel == (1 << (U8T_LINE_COLORSENSOR_C418 +1 )))         {name = "Color Sensor";}
    #ifdef M_DISTANCE
    if (channel == (1 << (U8T_LINE_LEFTDISTANCESENSOR_C418 +1 )))  {name = "Left Distance Sensor";}
    if (channel == (1 << (U8T_LINE_RIGHTDISTANCESENSOR_C418 +1 ))) {name = "Right Distance Sensor";}
    #endif
    if (channel == (1 << (U8T_LINE_LIDAR_C418 +1 )))               {name = "Lidar";}
    */
    return name;
}

// 3/3/2020
