// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/DriveTrainSubsystemBase.h"

class AutoSlalom : public frc2::CommandHelper<frc2::CommandBase, AutoSlalom> 
{
 public:
  AutoSlalom(DriveTrainSubsystemBase *pDrive);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;

 private:

  frc::Timer timer;

  int m_state = 0;
  double m_result = 0;
  int m_loopsUpdate = 0;

  double m_center = 0.75;

  bool m_IsFinished = false;

  double GetCameraState();
  void loop0();
  void loop1();
  void loop2();
  void loop3();
  void loop4();
  void loop5();
  void loop6();
  void loop7();
  void loop8();
  void loop9();

  DriveTrainSubsystemBase *m_pDrive = nullptr;
};
