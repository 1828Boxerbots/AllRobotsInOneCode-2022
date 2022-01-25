/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/DPDTSwitchDriver.h"
#include "Util.h"

DPDTSwitchDriver::DPDTSwitchDriver(int CHANNEL_A, int CHANNEL_B)
{
    m_pChannelA = new frc::DigitalInput(CHANNEL_A);
    m_pChannelB = new frc::DigitalInput(CHANNEL_B);
}

/**
 * This function tells you which scenario the switch is reporting.
 * 
 * If both channels of the switch are true, something is wrong with the switch
 * because they are controlled by pull-down resistors.
 */
int DPDTSwitchDriver::Get()
{
    //Util::DelayInSeconds(3);
    if (m_pChannelA->Get() && !(m_pChannelB->Get()))
    {
        return 1;
    }
    else if (!(m_pChannelA->Get()) && !(m_pChannelB->Get()))
    {
        return 2;
    }
    else if (!(m_pChannelA->Get()) && m_pChannelB->Get())
    {
        return 3;
    }
    else if (m_pChannelA->Get() && m_pChannelB->Get())
    {
        //Util::SendErrorAndCode("Autonomous Switch unresponsive", 132, "DPDTSwitchDriver.cpp");
        return -1;
    }
    return -1;
}

// working as of 2/15/20 (stop breaking it)
