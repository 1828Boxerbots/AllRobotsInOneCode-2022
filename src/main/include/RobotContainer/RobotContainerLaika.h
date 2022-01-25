/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/Laika/DriveTrainSubsystemLaika.h"
#include "RobotContainerBase.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerLaika : public RobotContainerBase
{
public:
  RobotContainerLaika();

  frc2::Command *GetAutonomousCommand() override;

  virtual void Init() {}
  virtual void DisableInit() {}
  void SetLiftButton();

private:
  // The robot's subsystems and commands are defined here...

  //Controller

  void ConfigureButtonBindings();
};
