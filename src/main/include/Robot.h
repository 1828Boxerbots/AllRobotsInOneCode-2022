/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>

#include "RobotContainer/RobotContainerRocky.h"
#include "RobotContainer/RobotContainerKurgan.h"
#include "RobotContainer/RobotContainerLaika.h"
#include "RobotContainer/RobotContainerSLAL.h"
#include "RobotContainer/RobotContainerC418.h"
#include "RobotContainer/RobotContainerLipALoop.h"

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

private:
  static void VisionThread();
  frc::Timer m_timer;
  units::second_t m_startTime = 0.0_s;
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc2::Command *m_autonomousCommand = nullptr;

  //RobotContainerRocky m_container;
  //RobotContainerSLAL m_container;
  RobotContainerKurgan m_container;
  //RobotContainerLaika m_container;
  //RobotContainerLipALoop m_container;
  //RobotContainerC418 m_container;
};
