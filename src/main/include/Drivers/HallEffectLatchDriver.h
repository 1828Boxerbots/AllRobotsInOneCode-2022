/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/DigitalInput.h>

class HallEffectLatchDriver
{
public:
  HallEffectLatchDriver(int port);

  /*
  * Hall Effect Latch
  * This sensor will pull the output low when a south pole is applied to the sensor. 
  * It will stay low until a north pole is applied.
  */
  bool Get();
  void Init();

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
  frc::DigitalInput *m_pDevice = nullptr;
};

// 2/14/20
