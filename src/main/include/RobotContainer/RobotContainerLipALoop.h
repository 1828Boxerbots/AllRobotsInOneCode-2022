/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/LipALoop/DriveTrainSubsystemLipALoop.h"
#include "subsystems/LipALoop/ArmSubsystemLipALoop.h"
#include "subsystems/LipALoop/WristSubsystemLipALoop.h"
#include "subsystems/LipALoop/HandSubsystemLipALoop.h"
#include "RobotContainerBase.h"
#include "subsystems/CameraSubsystemBase.h"
#include "Commands/PlayMove.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerLipALoop : public RobotContainerBase
{
public:
  RobotContainerLipALoop();

  frc2::Command *GetAutonomousCommand() override;

  virtual void Init() {}
  virtual void DisableInit() {}
  void SetRightBumper() override;
  void SetLeftBumper() override;
  void SetButtonA() override;
  void SetButtonB() override;
  void SetButtonX() override;
  void SetButtonY() override;
  void SetStartButton() override;
  void TeleopPeriodic() override;

private:
  // The robot's subsystems and commands are defined here...

  //Align Control
  void ConfigureButtonBindings();

  int serverVar = 1;
  int clietVar = 0;
  //std::shared_ptr<NetworkTable> netw;
  PlayMove* m_pPlayMove = nullptr;
  const char* PLAY_MOVE = "/u/c418_recording/recording_2021-03-22_17-15-55.bin";
};
