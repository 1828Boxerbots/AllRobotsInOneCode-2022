// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

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
class BenAutoBounce
    : public frc2::CommandHelper<frc2::CommandBase, BenAutoBounce> 
{
 public:
  BenAutoBounce(DriveTrainSubsystemBase* pDrive);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  constexpr static double TURN_RADIUS = 11;

  void BackwardsInInchGyro(double inch, double speed, double angleDeadZone = 1, double turnSpeed = 0.05);
  void SprinkleToAngle(double angle, double speed, units::second_t delay, double deadZone);

 private:
  DriveTrainSubsystemBase* m_pDrive = nullptr;
  bool m_isFinished = false;
  int m_state = 0;
  double m_turnRadius = 11;

  units::second_t m_delay = 0.05_s;

  void ProcessState0();
  void ProcessState1();
  void ProcessState2();
  void ProcessState3();
  void ProcessState4();
};
