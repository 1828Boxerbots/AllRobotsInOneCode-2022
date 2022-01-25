/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Util.h"

double Util::Limit(double value, double lowerLimit, double higherLimit)
{
    if (lowerLimit > higherLimit)
    {
        return value;
    }
    else if (value > higherLimit)
    {
        value = higherLimit;
    }
    else if (value < lowerLimit)
    {
        value = lowerLimit;
    }
    return value;
}

void Util::DelayInSeconds(units::second_t seconds)
{
    frc::Timer timer;
    //starts timer and gets start time and beginning current time
    timer.Start();
    timer.Reset();
    units::second_t startTime = timer.Get();
    units::second_t currentTime = timer.Get();
    //Keep looping until end time is reached
    while (currentTime - startTime < seconds)
    {
        //Gets current time and sends it to the smartdashboard for checking
        currentTime = timer.Get();
    }
    //Stops and resets timer used for driving forward
    timer.Stop();
    timer.Reset();
}

bool Util::CompareDouble(double value, double requiredValue, double tolerance)
{
    if ((value > requiredValue - tolerance) && (value < requiredValue + tolerance))
    {
        return true;
    }
    else
    {
        return false;
    }
    //Another way to write this is
    //return (value > requiredValue - tolerance) && (value < requiredValue + tolerance);
}

double Util::AbsMax(double input, double maxValue)
{
    // Just in case the max is negative
    maxValue = std::abs(maxValue);

    if (input > 0)
    {
        return std::min(input, maxValue);
    }
    else
    {
        return std::max(input, -maxValue);
    }
}

double Util::AbsMin(double input, double minValue)
{

    // Just in case the max is negative
    minValue = std::abs(minValue);

    if (input > 0)
    {
        return std::max(input, minValue);
    }
    else
    {
        return std::min(input, -minValue);
    }
}

double Util::Abs(double input)
{
    if(input < 0.0)
    {
        input = -input;
    }
    return input;
}

void Util::Log(std::string title, double value, std::string subsystemName)
{
    frc::SmartDashboard::PutNumber(subsystemName + " " + title, value);
}

void Util::Log(std::string title, int value, std::string subsystemName)
{
    frc::SmartDashboard::PutNumber(subsystemName + " " + title, value);
}

void Util::Log(std::string title, bool value, std::string subsystemName)
{
    frc::SmartDashboard::PutBoolean(subsystemName + " " + title, value);
}

void Util::Log(std::string title, std::string value, std::string subsystemName)
{
    frc::SmartDashboard::PutString(subsystemName + " " + title, value);
}

void Util::Log(std::string title, const char *value, std::string subsystemName)
{
    std::string newvalue = (std::string)value;
    frc::SmartDashboard::PutString(subsystemName + " " + title, newvalue);
}

/* 
*  Specialized error reporting (Adam's test)
*  
*  Allows you to report to the driver station with a custom error code.
*/
// void Util::SendErrorAndCode(const wpi::Twine &error, int32_t code)
// {
//     wpi::SmallString<128> temp;
//     HAL_SendError(1, code, 0, error.toNullTerminatedStringRef(temp).data(), "", "", 1);
// }

// /* 
// *  Overload of the other error function (Adam's test)
// *  
// *  Allows you to report to the driver station with a custom error code, and location.
// *
// *  Const Char* is just a string, or anything in quotes (e.g. "abc")
// */
// void Util::SendErrorAndCode(const wpi::Twine &error, int32_t code, const char *location)
// {
//     wpi::SmallString<128> temp;
//     HAL_SendError(1, code, 0, error.toNullTerminatedStringRef(temp).data(), location, "", 1);
// }
// Experimental functions added 3/5/2020

void Util::Log(std::string title, SpinSubsystemBase::FMSColors value, std::string subsystemName)
{
    std::string newvalue;

    switch (value)
    {
    case SpinSubsystemBase::FMSColors::BLUE:
        newvalue = "Blue";
        break;
    case SpinSubsystemBase::FMSColors::RED:
        newvalue = "Red";
        break;
    case SpinSubsystemBase::FMSColors::YELLOW:
        newvalue = "Yellow";
        break;
    case SpinSubsystemBase::FMSColors::GREEN:
        newvalue = "Green";
        break;
    default:
        newvalue = "Invalid";
        break;
    }

    frc::SmartDashboard::PutString(subsystemName + " " + title, newvalue);
}

std::string Util::TimeStampStr()
{
    //Grab current time from computer
    std::tm *pOut;
    std::time_t time = std::time(nullptr);
    pOut = localtime(&time);

    //Timestamp
    char str[2560];
    sprintf(str, "%04d-%02d-%02d_%02d-%02d-%02d", pOut->tm_year + 1900, pOut->tm_mon+1, pOut->tm_mday, pOut->tm_hour, 
        pOut->tm_min, pOut->tm_sec);
    
    Log("Util Stamp", str);
    return str;
}
