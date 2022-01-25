// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/SplineTests/SplineBounce.h"

SplineBounce::SplineBounce() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void SplineBounce::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SplineBounce::Execute() 
{
  frc::RamseteController controller1;
  GenerateTrajectory();
}

// Generates a trajectory for the robot to follow
void SplineBounce::GenerateTrajectory()
{
  const frc::Pose2d start{0.0_ft,0.0_ft,frc::Rotation2d(0.0_deg)};
  const frc::Pose2d end{0.0_ft,0.0_ft,frc::Rotation2d(0.0_deg)};

  std::vector<frc::Translation2d> interiorWaypoints
  {
    frc::Translation2d{0.0_ft, 0.0_ft},
    frc::Translation2d{0.0_ft, 0.0_ft}
  };

  frc::TrajectoryConfig config{12_fps, 12_fps_sq};
  config.SetReversed(false);

  auto trajectory = frc::TrajectoryGenerator::GenerateTrajectory(start, interiorWaypoints, end, config);
}


// Called once the command ends or is interrupted.
void SplineBounce::End(bool interrupted) {}

// Returns true when the command should end.
bool SplineBounce::IsFinished() 
{
  return false;
}
