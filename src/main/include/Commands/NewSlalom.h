// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveTrainSubsystemBase.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class NewSlalom
    : public frc2::CommandHelper<frc2::CommandBase, NewSlalom> {
 public:
  NewSlalom(DriveTrainSubsystemBase *pDrive);

  void Initialize() override;

  void Execute() override;

  void RotateToDegree(double degree, double speed);

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  DriveTrainSubsystemBase *m_pDrive;
  bool m_isFinished = false;

  double m_moveSpeed = 0.8;
  int m_height;
  int m_width;
  int m_roi;
  double m_deadZone = 25;
};
