// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "../../subsystems/DriveTrainSubsystemBase.h"
#include "../../subsystems/LoaderSubsystemBase.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class GalacticPathRedA
    : public frc2::CommandHelper<frc2::CommandBase, GalacticPathRedA> 
{
 public:
  
  // Constructor
  GalacticPathRedA(DriveTrainSubsystemBase *pDrive, LoaderSubsystemBase *pLoader, double radius = 11);

  // Does Nothing
  void Initialize() override;

  // Actually runs the command
  void Execute() override;

  // Does Nothing
  void End(bool interrupted) override;

  // Returns False
  bool IsFinished() override;

  // Moves to and picks up the first ball
  void GetBallOne();

  // Turns to face, drive toward, and pick up the second ball
  void GetBallTwo();

  // Turns to face, drive toward, and pick up the third ball
  void GetBallThree();

  // Turns to face and drive toward the end zone
  void ToEndZone();

  // Radius of the wheels in case TurnInInches is used
  constexpr static double TURN_RADIUS = 11;

private:

  // Object for the drivetrain
  DriveTrainSubsystemBase* m_pDrive = nullptr;

  // Object for the loader
  LoaderSubsystemBase* m_pLoader;

  // Current stage of the command 
  int m_state = 0;

  // Radius of the wheels in case TurnInInches is used
  double m_turnRadius = 11;
};
