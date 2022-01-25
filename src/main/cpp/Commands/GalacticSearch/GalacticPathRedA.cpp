// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/GalacticSearch/GalacticPathRedA.h"

GalacticPathRedA::GalacticPathRedA(DriveTrainSubsystemBase *pDrive, LoaderSubsystemBase *pLoader, double radius) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  m_pLoader = pLoader;
  m_turnRadius = radius;
  this->AddRequirements(pDrive);
  this->AddRequirements(pLoader);
}

// Called when the command is initially scheduled.
void GalacticPathRedA::Initialize() 
{

}

// Called repeatedly when this Command is scheduled to run
void GalacticPathRedA::Execute() 
{
  switch(m_state)
  {
    // Assume starting position facing first ball and directly in front of it
    case 0:
    GetBallOne();
    break;
    case 1:
    GetBallTwo();
    break;
    case 2:
    GetBallThree();
    break;
    case 3:
    ToEndZone();
    break;
  }
}

// Called once the command ends or is interrupted.
void GalacticPathRedA::End(bool interrupted) 
{

}

// Returns true when the command should end.
bool GalacticPathRedA::IsFinished() 
{
  return false;
}

// Start Zone -> Ball -> Pickup
void GalacticPathRedA::GetBallOne()
{
  m_pDrive->ForwardInInch(60,0,0.4); // Assume directly in front of ball, go forward to it
  m_pLoader->SetLoadMotor(0.6); // Load first ball to photogate
  Util::DelayInSeconds(0.5_s); // Wait while picking up
  m_pLoader->SetLoadMotor(0.0); // Stop loaders
  m_state = 1; // Go to next stage
}

// Turn to ball 2 -> Ball -> Pickup
void GalacticPathRedA::GetBallTwo()
{
  m_pDrive->TurnInDegrees(26.565 - 6.2,0.4); // Turn 26.565 degrees toward the second ball
  m_pDrive->ForwardInInch(67.082,0,0.4); // Move toward the ball, 67.082 is length of hypotenuse toward ball
  m_pLoader->SetLoadMotor(0.6,3); // Pick up the second ball; 3 denotes the Bottom 2 loaders
  Util::DelayInSeconds(0.5_s); // Wait while picking up
  m_pLoader->SetLoadMotor(0.0); // Stop loaders
  m_state = 2; // Go to next stage
}

// Turn to ball 3 -> Ball -> Pickup
void GalacticPathRedA::GetBallThree()
{
  m_pDrive->TurnInDegrees(-97.130 + 33.0,0.4); // Turn -97.130 degrees toward the third ball
  m_pDrive->ForwardInInch(94.86833,0,0.4); // Move toward the ball, 94.86833 is length of hypotenuse toward ball
    m_pLoader->SetLoadMotor(0.6,3); // Pick up the third ball; 3 denotes the Bottom 2 loaders
  Util::DelayInSeconds(0.5_s); // Wait while picking up
  m_pLoader->SetLoadMotor(0.0); // Stop loaders
  m_state = 3; // Go to next stage
}

// Turn to End Zone -> Forward to End Zone -> Stop
void GalacticPathRedA::ToEndZone()
{
  m_pDrive->TurnInDegrees(71.565,0.4); // Turn 71.565 degrees toward the end zone
  m_pDrive->ForwardInInch(94.86833,0,0.4); // Move toward the end zone, 180 inches away
  m_state = 4; // End
}

