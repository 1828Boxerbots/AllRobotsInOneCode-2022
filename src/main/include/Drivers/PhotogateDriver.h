/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/DigitalInput.h>

class PhotogateDriver
{
public:
  PhotogateDriver(int port);

  bool Get();
  void Init();

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
  frc::DigitalInput *m_pDevice = nullptr;
};

// 2/14/20
