/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "..\subsystems\LoaderSubsystemBase.h"
#include "..\subsystems\ShooterSubsystemBase.h"
#include "..\subsystems\DriveTrainSubsystemBase.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ShootLoadCommand
    : public frc2::CommandHelper<frc2::CommandBase, ShootLoadCommand>
{
public:
  ShootLoadCommand(LoaderSubsystemBase *pLoader, ShooterSubsystemBase *pShooter, DriveTrainSubsystemBase *pDrive, double encoderSetting, double shootSpeed, double driveSpeed, double lidarDistanceLow, double lidarDistanceHigh);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  LoaderSubsystemBase *m_pLoader = nullptr;
  ShooterSubsystemBase *m_pShooter = nullptr;
  DriveTrainSubsystemBase *m_pDrive = nullptr;

  double m_encoderWanted = -5900.0;
  double m_shootSpeed = 1.0;
  double m_driveSpeed = 0.5;
  double m_loaderSpeed = 1.0;
  double m_encoderTolerance = 100.0;
  units::second_t m_oneBallTime = 0.5_s;
  double m_lidarLow = 90.0;
  double m_lidarHigh = 120.0;

  bool m_isFinished = false;
  bool m_isBusy = false;
};
