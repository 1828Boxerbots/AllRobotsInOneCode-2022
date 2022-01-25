/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "..\subsystems\DriveTrainSubsystemBase.h"

class MoveTankCommand
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 MoveTankCommand>
{
public:
  MoveTankCommand(DriveTrainSubsystemBase *pDrive, double left = 1.0, double right = 1.0);

  void Initialize() override;
  void Execute() override;

private:
  DriveTrainSubsystemBase *m_pDrive;
  double m_left = 1.0;
  double m_right = 1.0;
};
