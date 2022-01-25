/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

// Might actually be analog, but not important yet.
#include <frc/Encoder.h>

class RotaryMagneticEncoderDriver
{
public:
  RotaryMagneticEncoderDriver();

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
  frc::Encoder *m_pDevice = nullptr;
};

// 2/14/20
