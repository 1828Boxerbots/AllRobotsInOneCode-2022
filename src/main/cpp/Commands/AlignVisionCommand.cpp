/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/*
#include "Commands/AlignVisionCommand.h"

AlignVisionCommand::AlignVisionCommand(DriveTrainSubsystemBase *pDrive, CameraSubsystemBase *pCamera) 
{
  m_pDrive = pDrive;
  m_pCamera = pCamera;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(pDrive);
  AddRequirements(pCamera);
}

// Called when the command is initially scheduled.
void AlignVisionCommand::Initialize() 
{
}

// Called repeatedly when this Command is scheduled to run
void AlignVisionCommand::Execute() 
{
  //m_pCamera->Tick();
  int dir = m_pCamera->WhereToTurn();
  if (dir == CameraSubsystemBase::GO_LEFT)
  {
    m_pDrive->TurnLeft();
  }
  else if (dir == CameraSubsystemBase::GO_RIGHT)
  {
    m_pDrive->TurnRight();
  }
  else if (dir == CameraSubsystemBase::STOP)
  {
    m_pDrive->Stop();
    m_isFinished = true;
  }
  else if (dir == CameraSubsystemBase::CANT_FIND_IMAGE)
  {
    m_pDrive->TurnLeft(1.0);
  }
}

// Called once the command ends or is interrupted.
void AlignVisionCommand::End(bool interrupted) 
{
    m_pDrive->Stop();
}

// Returns true when the command should end.
bool AlignVisionCommand::IsFinished() 
{ 
  return m_isFinished; 
}
*/

//COMMENTED OUT FOR RESTART PURPOSES. FOR REFERENCE ONLY
