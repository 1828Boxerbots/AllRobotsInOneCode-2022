// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/BackupChallengeOne.h"

BackupChallengeOne::BackupChallengeOne(DriveTrainSubsystemBase* pDrive)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void BackupChallengeOne::Initialize() 
{
  m_isFinished = false;
  types = 1;

  int height;
  int width;
  m_pDrive->GetVisionSize(&height, &width);
  m_pDrive->SetVisionCrop(0, height*0.75, width, height*0.25);
}

// Called repeatedly when this Command is scheduled to run
void BackupChallengeOne::Execute() 
{
  Util::Log("ChallengeOnefinished", m_isFinished);
  if(m_isFinished == false)
  {
    switch(types)
    {
    case 1:
      //Going around first cone
      m_pDrive->ForwardInInchGyro(110, 0.3);
      m_pDrive->IMUArcade(0.6, 0.2, -335);
      m_pDrive->ForwardInInchGyro(36, 0.3);
      m_pDrive->SetLookingColorV(OldCameraVision::RED_CONE_A);
      m_pDrive->AlignWithVision(-0.5, 30, true);
      m_pDrive->ForwardInInchGyro(10, 0.6);
      //Going around second cone
      m_pDrive->IMUArcade(0.6, -0.2, 280);
      //m_pDrive->ForwardInInchGyro(15, 0.6);
      m_pDrive->SetLookingColorV(OldCameraVision::PURPLE_BOTTLE_A);
      m_pDrive->AlignWithVision(-0.75, 30, false);
      m_pDrive->ForwardInInchGyro(15, 0.6);
      //Going around third cone
      //m_pDrive->ForwardInInchGyro(7, 0.6);
      m_pDrive->IMUArcade(0.6, -0.2, 200);
      // m_pDrive->ForwardInInchGyro(24, 0.4);
      // m_pDrive->IMUArcade(0.6, -0.2, 70);
      m_pDrive->ForwardInInchGyro(12,0.6); 
      m_pDrive->SetLookingColorV(OldCameraVision::RED_CONE_A);
      m_pDrive->AlignWithVision(1.0, 30, true);
      m_pDrive->ForwardInInchGyro(36, 0.5);
      //Coming back to start zone 
      m_pDrive->SetLookingColorV(OldCameraVision::ORANGE_CONE);
      m_pDrive->AlignWithVision(-1.0, 30, true);
      m_pDrive->ForwardInInchGyro(25, 0.5);
      m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_N);
      m_pDrive->AlignWithVision(0.0, 30, true);
      //m_pDrive->ForwardInInch(60,0.0,0.7);
      //m_pDrive->ForwardInInch(240, 0.0, 0.4);
      break;
    case 2:
      break;
    case 3:
      break;
    }
  }

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void BackupChallengeOne::End(bool interrupted) {}

// Returns true when the command should end.
bool BackupChallengeOne::IsFinished() 
{
  return m_isFinished;
}
