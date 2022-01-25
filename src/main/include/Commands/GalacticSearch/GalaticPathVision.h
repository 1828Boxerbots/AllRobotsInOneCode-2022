// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "..\..\subsystems\LoaderSubsystemBase.h"
#include "..\..\subsystems\DriveTrainSubsystemBase.h"
#include "../../Drivers/CameraDrivers/OldCameraVision.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class GalaticPathVision
    : public frc2::CommandHelper<frc2::CommandBase, GalaticPathVision> {
 public:
  GalaticPathVision(DriveTrainSubsystemBase *pDrive, LoaderSubsystemBase *pLoader);

  void Initialize() override;

  void Execute() override;

  int CheckRun();
  void RunRedOne();
  void RunRedTwo();
  void RunBlueOne();
  void RunBlueTwo();

  void RotateToEnd();
  void FaceBall(bool turnLeft = false, units::second_t delay = 0.04_s, double speed = -666);
  void RotateToDegree(double degree, double speed = -666);

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  DriveTrainSubsystemBase *m_pDrive;
  LoaderSubsystemBase *m_pLoader;
  bool m_isFinished = false;

  OldCameraVision::VisionColors m_color = OldCameraVision::YELLOW_LEMON_M;

  double m_moveSpeed = 0.8;
  double m_loaderSpeed = 0.6;
  double m_turnSpeed = 0.1;
  double rioW = 60;
  int m_deadZone = 6;
  double m_startAngle;
  double m_angleDed = 5;

  enum RunIteration{RED_ONE, RED_TWO, BLUE_ONE, BLUE_TWO};

  RunIteration m_iteration;

  int m_height;
  int m_width;
};
