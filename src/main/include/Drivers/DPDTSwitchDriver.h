/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/DigitalInput.h>

#include "Util.h"

class DPDTSwitchDriver
{
public:
  DPDTSwitchDriver(int CHANNEL_A, int CHANNEL_B);

  /**
   * This is the switch that we will be using to determine the autonomous scenarios.
   * The Get() function will return an integer based on the position of the switch.
   * Up position: 1
   * Middle Position: 2
   * Down Position: 3
   * 
   * If for some reason the sensor breaks, it will return -1 and throw an error to the driver station.
   */
  int Get();
  void Init();

private:
  frc::DigitalInput *m_pChannelA = nullptr;
  frc::DigitalInput *m_pChannelB = nullptr;
};

// 2/14/20
