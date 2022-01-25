/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/AnalogInput.h>

class HallEffectAnalogDriver
{
public:
  HallEffectAnalogDriver(int port);

  /*
  * This sensor outputs a voltage based on the strength of a magnetic pole. 0V for a strong south pole, 2V for a strong north pole, and 1V for no pole detected. 
  * Use this for position sensing within the range  of the sensor (about 1-2” (3 - ~5mm), depending on magnet strength)
  */
  bool Get();
  void Init() {}

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
  frc::AnalogInput *m_pDevice = nullptr;
};

// 2/14/20
