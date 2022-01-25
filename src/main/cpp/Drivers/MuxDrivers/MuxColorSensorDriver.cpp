/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/MuxDrivers/MuxColorSensorDriver.h"

/**
 * This is the constructor. This sets the channel of the Multiplexer to whatever you set breakoutchannel to. 
 * It then creates an instance of the rev color sensor.
 * 
 * i2cport is the address for the color sensor
 * breakout is the multiplexer object
 * breakoutChannel is the channel that we want the color sensor to be on (U8T_LINE color sensor in constants)
 */
MuxColorSensorDriver::MuxColorSensorDriver(frc::I2C::Port i2cPort, I2CMultiplexerDriver &breakout, uint8_t breakoutChannel) : m_breakout(breakout),
                                                                                                                              m_breakoutChannel(breakoutChannel)
{
    SetActive();
    //m_pColorSensor = new rev::ColorSensorV3(i2cPort);
}

/**
 *  This sets the multiplexer to whichever channel you want.
 * 
 *  The channels are defined as U8T_LINE... in Constants.
 * 
 *  This is called in every function of the Color sensor so
 *  you do not need to do it manually.
 * 
 *  I will call it everywhere anyways just to be safe. It can't hurt.
 */
void MuxColorSensorDriver::SetActive()
{
    m_breakout.SetChannel(1 << (m_breakoutChannel));
}

/**
 *  Uses the color sensor to find the color. 
 *  Returns an FMS Color.
 * 
 *  Also logs what it's seeing to the dashboard.
 */
SpinSubsystemBase::FMSColors MuxColorSensorDriver::GetColor()
{
    return SpinSubsystemBase::FMSColors::INVALID;
    //SetActive();
    //frc::Color detectedColor = m_pColorSensor->GetColor();

    //std::string message;

    //SpinSubsystemBase::FMSColors output;

    // if (IsRed(detectedColor.red, detectedColor.green, detectedColor.blue))
    // {
    //     output = SpinSubsystemBase::FMSColors::RED;
    //     message = "Red";
    // }
    // else
    // {
    //     if (IsGreen(detectedColor.red, detectedColor.green, detectedColor.blue))
    //     {
    //         output = SpinSubsystemBase::FMSColors::GREEN;
    //         message = "Green";
    //     }
    //     else
    //     {
    //         if (IsBlue(detectedColor.red, detectedColor.green, detectedColor.blue))
    //         {
    //             output = SpinSubsystemBase::FMSColors::BLUE;
    //             message = "Blue";
    //         }
    //         else
    //         {
    //             if (IsYellow(detectedColor.red, detectedColor.green, detectedColor.blue))
    //             {
    //                 output = SpinSubsystemBase::FMSColors::YELLOW;
    //                 message = "Yellow";
    //             }
    //             else
    //             {
    //                 output = SpinSubsystemBase::FMSColors::INVALID;
    //                 message = "Invalid";
    //             }
    //         }
    //     }
    //}

    //Util::Log("Color Sensor Driver Color", message, "Color Sensor Driver");
    //return SpinSubsystemBase::FMSColors::INVALID;
}

/**
 *  Returns a string that tells you which color the sensor is seeing.
 * 
 *  Useful for telemetry, or to see if there's an FMSColors error.
 */
std::string MuxColorSensorDriver::GetColorString()
{
    SetActive();

    std::string retval;
    SpinSubsystemBase::FMSColors temp = GetColor();
    switch (temp)
    {
    case (SpinSubsystemBase::FMSColors::RED):
        retval = (std::string) "Red";
        break;
    case (SpinSubsystemBase::FMSColors::YELLOW):
        retval = (std::string) "Yellow";
        break;
    case (SpinSubsystemBase::FMSColors::BLUE):
        retval = (std::string) "Blue";
        break;
    case (SpinSubsystemBase::FMSColors::GREEN):
        retval = (std::string) "Green";
        break;
    case (SpinSubsystemBase::FMSColors::INVALID):
        retval = (std::string) "Invalid";
        break;
    default:
        retval = (std::string) "ERROR";
    }
    return retval;
}

// figures out if the color is red
bool MuxColorSensorDriver::IsRed(double R, double G, double B)
{
    SetActive();
    if (R >= RED_LOW_R && R <= RED_HIGH_R)
    {
        if (G >= RED_LOW_G && G <= RED_HIGH_G)
        {
            if (B >= RED_LOW_B && B <= RED_HIGH_B)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// figures out if the color is green
bool MuxColorSensorDriver::IsGreen(double R, double G, double B)
{
    SetActive();
    if (R >= GREEN_LOW_R && R <= GREEN_HIGH_R)
    {
        if (G >= GREEN_LOW_G && G <= GREEN_HIGH_G)
        {
            if (B >= GREEN_LOW_B && B <= GREEN_HIGH_B)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// figures out if the color is blue
bool MuxColorSensorDriver::IsBlue(double R, double G, double B)
{
    SetActive();
    if (R >= BLUE_LOW_R && R <= BLUE_HIGH_R)
    {
        if (G >= BLUE_LOW_G && G <= BLUE_HIGH_G)
        {
            if (B >= BLUE_LOW_B && B <= BLUE_HIGH_B)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// figures out if the color is yellow
bool MuxColorSensorDriver::IsYellow(double R, double G, double B)
{
    SetActive();
    if (R >= YELLOW_LOW_R && R <= YELLOW_HIGH_R)
    {
        if (G >= YELLOW_LOW_G && G <= YELLOW_HIGH_G)
        {
            if (B >= YELLOW_LOW_B && B <= YELLOW_HIGH_B)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/** Will tell you if the detected color matches three or more set colors.
 * 
 *  When you see this, fix the bounds so that it can distinguish between the correct colors.
 * 
 *  This is already called in DetectOverlap, so you don't need to run this separately.
 */
void MuxColorSensorDriver::DetectTripleOverlap(bool isRed, bool isBlue, bool isGreen, bool isYellow)
{
    SetActive();
    // if (isRed && isYellow && isGreen)
    // {
    //     Util::SendErrorAndCode("Red, Yellow, and Green overlap", 107, m_fileLoc);
    // }
    // if (isRed && isYellow && isBlue)
    // {
    //     Util::SendErrorAndCode("Red, Yellow, and Blue overlap", 108, m_fileLoc);
    // }
    // if (isRed && isBlue && isGreen)
    // {
    //     Util::SendErrorAndCode("Red, Blue, and Green overlap", 109, m_fileLoc);
    // }
    // if (isBlue && isYellow && isGreen)
    // {
    //     Util::SendErrorAndCode("Blue, Yellow, and Green overlap", 110, m_fileLoc);
    // }
    // if (isBlue && isYellow && isGreen && isRed)
    // {
    //     Util::SendErrorAndCode("All colors overlap", 111, m_fileLoc);
    // }
}

/**
 *  This detects overlaps in color and sends you an error.
 * 
 *  If you see an overlap error, check which colors the computer is confusing
 *  and change their RGB bounds so that it can distinguish between them.
 */
void MuxColorSensorDriver::DetectOverlap()
{
    // SetActive();
    // frc::Color detectedColor = m_pColorSensor->GetColor();

    // bool isRed = IsRed(detectedColor.red, detectedColor.green, detectedColor.blue);
    // bool isGreen = IsGreen(detectedColor.red, detectedColor.green, detectedColor.blue);
    // bool isBlue = IsBlue(detectedColor.red, detectedColor.green, detectedColor.blue);
    // bool isYellow = IsYellow(detectedColor.red, detectedColor.green, detectedColor.blue);

    // DetectTripleOverlap(isRed, isBlue, isGreen, isYellow);

    // if (isRed && isYellow)
    // {
    //     Util::SendErrorAndCode("Red overlaps with Yellow", 101, m_fileLoc);
    // }
    // if (isRed && isGreen)
    // {
    //     Util::SendErrorAndCode("Red overlaps with Green", 102, m_fileLoc);
    // }
    // if (isRed && isBlue)
    // {
    //     Util::SendErrorAndCode("Red overlaps with Blue", 103, m_fileLoc);
    // }
    // if (isYellow && isGreen)
    // {
    //     Util::SendErrorAndCode("Yellow overlaps with Green", 104, m_fileLoc);
    // }
    // if (isYellow && isBlue)
    // {
    //     Util::SendErrorAndCode("Yellow overlaps with Blue", 105, m_fileLoc);
    // }
    // if (isBlue && isGreen)
    // {
    //     Util::SendErrorAndCode("Blue overlaps with Green", 106, m_fileLoc);
    // }
}

void MuxColorSensorDriver::ReturnAllColors()
{
    SetActive();
    //frc::Color detectedColor = m_pColorSensor->GetColor();

    // Util::Log("Red", detectedColor.red, "Color Sensor Driver");
    // Util::Log("Green", detectedColor.green, "Color Sensor Driver");
    // Util::Log("Blue", detectedColor.blue, "Color Sensor Driver");
}

// Completed 3/3/2020 , untested
