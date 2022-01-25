/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../subsystems/DriveTrainSubsystemBase.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class MoveToDistanceCommand
    : public frc2::CommandHelper<frc2::CommandBase, MoveToDistanceCommand>
{
public:
  MoveToDistanceCommand(DriveTrainSubsystemBase *pDrive, double targetDistance = 0.0, double speed = 1.0);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  DriveTrainSubsystemBase *m_pDrive = nullptr;
  bool m_isFinished = false;
  double m_targetDistance = 0.0;
  double m_toleranceValue = 10.0;
};
