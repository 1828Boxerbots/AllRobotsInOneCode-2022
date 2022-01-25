/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerLaika.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerLaika::RobotContainerLaika()
{

  m_pDrive = new DriveTrainSubsystemLaika;
  // Configure the button bindings
  ConfigureButtonBindings();
  m_pDrive->Init();
  SetDrive();
}

void RobotContainerLaika::ConfigureButtonBindings()
{
  //Laika Shooter - May not work rn - 2/5/20
  SetLeftBumper();
  SetRightBumper();

  SetLiftButton();
}

frc2::Command *RobotContainerLaika::GetAutonomousCommand()
{
  // An example command will be run in autonomous
  return 0;
}

void RobotContainerLaika::SetLiftButton()
{
}
