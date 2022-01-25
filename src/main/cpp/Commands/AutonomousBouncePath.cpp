// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "../../include/Commands/AutonomousBouncePath.h"


AutonomousBouncePath::AutonomousBouncePath(DriveTrainSubsystemBase* pDrive, double radius) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  m_turnRadius = radius;
  this->AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void AutonomousBouncePath::Initialize() 
{
  m_state = 3;
}

// Called repeatedly when this Command is scheduled to run
void AutonomousBouncePath::Execute() 
{
  switch(m_state)
  {
    // case 0:
    // ProcessState0();
    // break;
    // case 1:
    // ProcessState1();
    // break;
    // case 2:
    // ProcessState2();
    // break;
    case 3:
    ProcessState3();
    break;
    case 4:
    ProcessState4();
  }
}

// Called once the command ends or is interrupted.
void AutonomousBouncePath::End(bool interrupted) 
{

}

// Returns true when the command should end.
bool AutonomousBouncePath::IsFinished() 
{
  return false;
}

void AutonomousBouncePath::ProcessState0()
{
  if(m_state == 0)
  {
    m_pDrive->ForwardInInch(10,0,0.5);
    m_pDrive->TimedArcade(0.6,-0.2,1.3_s);
    m_pDrive->ForwardInInch(20,0,0.5);
    m_state = 1;
  }
}

void AutonomousBouncePath::ProcessState1()
{
  if(m_state == 1)
  {
    ///m_pDrive->TurnInDegrees(165,0.5, m_turnRadius); /original
    m_pDrive->TimedArcade(-0.9,-0.08,1.85_s); // Back waay out of the first bottle, and to the right
    m_pDrive->TimedArcade(-0.6,-0.3,1.42_s); // Reverse semicircle around cone
    m_pDrive->TimedArcade(-0.7,0.05,1.67_s); // Straight back into the second cone
    m_pDrive->ForwardInInch(70,0.0,0.7); // Straight forward
    m_state = 2;
  }
}

void AutonomousBouncePath::ProcessState2()
{
  if(m_state == 2)
  {
    m_pDrive->TimedArcade(0.6, -0.15, 2.55_s); // Wide turn around cones
    m_pDrive->ForwardInInch(85,0,0.7); // Forward to third cone
    m_pDrive->TimedArcade(-0.5,-0.17, 1.2_s); // Reverse into end
    ///m_pDrive->ForwardInInch(90,0,0.5);
    m_state = 3;
  }
}

void AutonomousBouncePath::ProcessState3()
{
  if(m_state == 3)
  {
    m_pDrive->ForwardInInchGyro(49); // Move out of the starting zone
    m_pDrive->TurnInDegreesGyro(90); // Turn to face the first target
    m_pDrive->ForwardInInchGyro(44); // Go punch that target
    m_pDrive->ForwardInInchGyro(-14); // Back up a little
    m_pDrive->TurnInDegreesGyro(22); // Turn a shallow angle
    m_pDrive->ForwardInInchGyro(-80); // Go all the way back
    m_pDrive->TurnInDegreesGyro(23); // Turn a little more so the back is facing forward
    m_pDrive->ForwardInInchGyro(-42.5); // Back up
    m_pDrive->TurnInDegreesGyro(90); // Turn to face mostly away from the second target
    m_pDrive->ForwardInInchGyro(-42.5); // Back up a little more
    m_pDrive->TurnInDegreesGyro(45); // Turn to face away from the second target
    m_pDrive->ForwardInInchGyro(-75); // Back all the way into the second target
    m_pDrive->ForwardInInchGyro(75); // Move all the way back forward
    m_pDrive->TurnInDegreesGyro(45); // Turn left
    m_pDrive->ForwardInInchGyro(42.5); // Move forward
    m_pDrive->TurnInDegreesGyro(90); // Turn again to get closer to the third target
    m_pDrive->ForwardInInchGyro(42.5); // Move forward into position for the third target
    m_pDrive->TurnInDegreesGyro(45); // Face the third target
    m_pDrive->ForwardInInchGyro(75); // Run all the way into the third target
    m_pDrive->ForwardInInchGyro(-15); // Back out a little
    m_pDrive->TurnInDegreesGyro(45); // Turn to face away from the end zone
    m_pDrive->ForwardInInchGyro(-42.5); // Back into the end zone
    m_state = 4;
  }
}

void AutonomousBouncePath::ProcessState4()
{
  if(m_state == 4)
  {
    //Turn Backwards into first Bottle
    m_pDrive->ForwardInInchGyro(10,-0.5);
    m_pDrive->TimedArcade(-0.6,-0.2,1.3_s);
    //Go forwards a little
    m_pDrive->ForwardInInchGyro(20,-0.5);
    //Turn to look for a green cone on D3
    m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_N);
    m_pDrive->AlignWithVision(0.75, 30, false, false);
    //Move Forward
    m_pDrive->ForwardInInchGyro(80,-0.5);
    //Go around cone
    m_pDrive->TimedArcade(0.6,-0.2,1.3_s);
    //MoveForward to purple bottle until you can see it
    m_pDrive->SetLookingColorV(OldCameraVision::PURPLE_BOTTLE_N);
    double cameraImage = m_pDrive->WhereToTurn();
    // while(cameraImage<-2.0)
    // {
    //   m_pDrive->ForwardInInchGyro(10,0.3);
    //   cameraImage = m_pDrive->WhereToTurn();
    // }
    // //Move Forward to purple bottle until you can't see it
    // while(cameraImage>-2.0)
    // {
    //   if(cameraImage<0.0)
    //   {
    //     m_pDrive->MoveArcade(0.3, -0.05);
    //   }
    //   else if(cameraImage>0)
    //   {
    //     m_pDrive->MoveArcade(0.3, 0.05);
    //   }
    //   else
    //   {
    //     m_pDrive->MoveArcade(0.3, 0.0);
    //   }
    //   cameraImage = m_pDrive->WhereToTurn();
    // }
    m_pDrive->ForwardInInchGyro(50,0.5);
    m_pDrive->AlignWithVision(0.0,30,true,false);
    m_pDrive->ForwardInInchGyro(50,0.5);
    //Turn To Absolute Angle
    m_pDrive->RotateToDegreeAbsolute(-90,0.3,2);
    //Move Back
    m_pDrive->ForwardInInchGyro(100, -0.3);
    //Turn right to look for a cone on the left
    m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_N);
    m_pDrive->AlignWithVision(-1.0,30,true, false);
    //Go Forward
    m_pDrive->ForwardInInchGyro(30,0.3);
    //Go around the cone to the left
    m_pDrive->TimedArcade(0.6,-0.2,1.3_s);
    //MoveForward to purple bottle until you can see it
    m_pDrive->SetLookingColorV(OldCameraVision::PURPLE_BOTTLE_N);
    cameraImage = m_pDrive->WhereToTurn();
    while(cameraImage<-2.0)
    {
      m_pDrive->Forward(0.5);
    }
    //Move Forward to purple bottle until you can't see it
    while(cameraImage>-2.0)
    {
      if(cameraImage<0.0)
      {
        m_pDrive->MoveArcade(0.3, -0.05);
      }
      else if(cameraImage>0.0)
      {
        m_pDrive->MoveArcade(0.3, 0.05);
      }
      else
      {
        m_pDrive->MoveArcade(0.3, 0.0);
      }
      cameraImage = m_pDrive->WhereToTurn();
    }
    //Turn backward into the finish
    m_pDrive->TimedArcade(-0.6,-0.2,1.3_s);

  }
}