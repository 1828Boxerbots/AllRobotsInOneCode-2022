/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/DigitalInput.h>

class HallEffectSwitchDriver
{
public:
  HallEffectSwitchDriver(int port);

  /*
  *  Hall Effect Switch
  *  This Sensor will latch low with a south pole magnetic field and will be high
  *  impedance with a north pole present
  */
  bool Get();
  void Init() {}

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
  frc::DigitalInput *m_pDevice = nullptr;
};

// 2/14/20
