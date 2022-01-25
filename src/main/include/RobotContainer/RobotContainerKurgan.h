/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/Kurgan/DriveTrainSubsystemKurgan.h"
#include "subsystems/Kurgan/LoaderSubsystemKurgan.h"
#include "subsystems/Kurgan/ShooterSubsystemKurgan.h"
#include "RobotContainerBase.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerKurgan : public RobotContainerBase
{
public:
  RobotContainerKurgan();

  frc2::Command *GetAutonomousCommand() override;

  void SetButtonA() override;
  void SetButtonB() override;

  void TeleopPeriodic() override;

  virtual void Init()
  {
    m_pDrive->Init();
    m_pLoader->SetLoadMotor(0.0);
  }
  virtual void DisableInit() { m_pLoader->SetLoadMotor(0.0); }

private:
  // The robot's subsystems and commands are defined here...

  void ConfigureButtonBindings();
  void InitializeAutonomousFunctions();
  frc2::SequentialCommandGroup *m_pAutoHouse = nullptr;
};
