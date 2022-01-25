// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../include/subsystems/DriveTrainSubsystemBase.h"
#include "../include/subsystems/ShooterSubsystemBase.h"
#include "../include/subsystems/LoaderSubsystemBase.h"
#include "../include/Util.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoLineUpShootCommand
    : public frc2::CommandHelper<frc2::CommandBase, AutoLineUpShootCommand>
{
 public:
  AutoLineUpShootCommand(DriveTrainSubsystemBase *pDrive, double wantedDistance, ShooterSubsystemBase *pShoot, LoaderSubsystemBase *pLoad);

  void Initialize() override;

  void Execute() override;

  void ForwardLidarGyro(double wantedDistance, double speed);

  void End(bool interrupted) override;

  bool IsFinished() override;

private: 
  DriveTrainSubsystemBase* m_pDrive = nullptr;
  ShooterSubsystemBase* m_pShoot = nullptr;
  LoaderSubsystemBase* m_pLoad = nullptr;
  bool m_isFinished = false;
  double m_wantedDistance = 0;
};
