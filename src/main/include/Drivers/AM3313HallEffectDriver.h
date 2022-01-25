/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/DigitalInput.h>

class AM3313HallEffectDriver
{
public:
  AM3313HallEffectDriver(int port);

  /*
  * Hall Effect Sensor
  * Sensor is driven low in the presence of a magnetic field, and high impedance
  * when there is no magnet present
  * Use this as a limit switch.
  */
  bool Get();
  void Init();

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
  frc::DigitalInput *m_pDevice = nullptr;
};

// Working as of 2/14/20
