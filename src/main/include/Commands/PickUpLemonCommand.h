// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

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
class PickUpLemonCommand
    : public frc2::CommandHelper<frc2::CommandBase, PickUpLemonCommand> {
 public:
  PickUpLemonCommand(LoaderSubsystemBase *pLoader
  , ShooterSubsystemBase *pShooter
  , DriveTrainSubsystemBase *pDrive
  , double moveSpeed = 1.0
  , double loadSpeed = 1.0
  , OldCameraVision::VisionColors colorEnd = OldCameraVision::RED_CONE_N
  , double deadzoneRange = 50.0
  , OldCameraVision::VisionColors color = OldCameraVision::YELLOW_LEMON_A);

  void Initialize() override;

  void Execute() override;

  void stateZero();
  void stateOne();
  void stateTwo();
  void stateThree();
  void stateFour();
  void stateFive();
  void stateSix();
  void stateSeven();
  void SetIsFinished(bool value);

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    LoaderSubsystemBase *m_pLoader = nullptr;
    ShooterSubsystemBase *m_pShooter = nullptr;
    DriveTrainSubsystemBase *m_pDrive = nullptr;

    double m_centerScreen = -0.7;
    double m_deadzoneRange = 40;
    double m_motorSpeed = 0.4;
    double m_loaderSpeed = 1.0;
    double m_result;
    int m_state = 0;
    int m_iteration = 0;
    OldCameraVision::VisionColors m_color;
    OldCameraVision::VisionColors m_colorEnd;

    bool m_isFinished = false;
};
