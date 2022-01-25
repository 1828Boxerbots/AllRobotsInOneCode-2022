// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/DriveTrainSubsystemBase.h"
#include "../Drivers/CameraDrivers/OldCameraVision.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class BenAutoBarrel
    : public frc2::CommandHelper<frc2::CommandBase, BenAutoBarrel> {
 public:
  BenAutoBarrel(DriveTrainSubsystemBase* pDrive);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  DriveTrainSubsystemBase* m_pDrive = nullptr;
  bool m_isFinished = false;
  double m_moveSpeed = 1;
  double m_slitherSpeed = 0.1;
};
