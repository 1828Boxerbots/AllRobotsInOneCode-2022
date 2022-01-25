/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "..\subsystems\ArmSubsystemBase.h"
#include "..\subsystems\SpinSubsystemBase.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class SpinWithArm
    : public frc2::CommandHelper<frc2::CommandBase, SpinWithArm>
{
public:
  enum SpinSelector
  {
    UseSpinMotor,
    UseSpinWithColor,
    UseSpinToColor,
    UseSpinStop,
    UseArm
  };

  SpinWithArm(ArmSubsystemBase *pArm, SpinSubsystemBase *pSpinner, enum SpinSelector selector, double speed, int wantedRotation,
              ArmSubsystemBase::ArmPositions armPos);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  SpinSubsystemBase *m_pSpinner = nullptr;
  ArmSubsystemBase *m_pArm = nullptr;
  enum SpinSelector m_selector;
  ArmSubsystemBase::ArmPositions m_armPos;
  double m_speed;
  int m_wantedRotation;
  bool m_isFinished;
};
