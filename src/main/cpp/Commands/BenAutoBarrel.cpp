// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/BenAutoBarrel.h"

BenAutoBarrel::BenAutoBarrel(DriveTrainSubsystemBase* pDrive)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void BenAutoBarrel::Initialize() 
{
  m_isFinished = false;

  int height;
  int width;
  m_pDrive->GetVisionSize(&height, &width);
  m_pDrive->SetVisionCrop(0, height*0.75, width, height*0.25);
}

// Called repeatedly when this Command is scheduled to run
void BenAutoBarrel::Execute() 
{
  Util::Log("ChallengeOnefinished", m_isFinished);
  if(m_isFinished == false)
  {
    //Going around first cone
    m_pDrive->ForwardInInchGyro(69, m_moveSpeed, 1, m_slitherSpeed);
    m_pDrive->IMUArcade(0.5, 0.15, -340);
    m_pDrive->ForwardInInchGyro(32, m_moveSpeed);
    m_pDrive->SetLookingColorV(OldCameraVision::RED_CONE_A);
    m_pDrive->AlignWithVision(-0.85, 30);
    m_pDrive->ForwardInInchGyro(12, m_moveSpeed, 1, m_slitherSpeed);
    //Going around second cone
    m_pDrive->IMUArcade(0.5, -0.15, 290);
    m_pDrive->ForwardInInchGyro(24, m_moveSpeed, 1, m_slitherSpeed);
    m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_A);
    m_pDrive->AlignWithVision(-0.9, 30, false, false);
    m_pDrive->ForwardInInchGyro(36, m_moveSpeed, 1, m_slitherSpeed);
    //Going around third cone
    m_pDrive->IMUArcade(0.4, -0.12, 190);
    Util::DelayInSeconds(0.1_s);
    m_pDrive->RotateToDegreeAbsolute(177, 0.15, 1);
    //Move to end
    m_pDrive->ForwardInInchGyro(232, m_moveSpeed, 1, m_slitherSpeed);
    // m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_A);
    // m_pDrive->AlignWithVision(0, 20, false, false);
    //m_pDrive->ForwardInInchGyro(76, m_moveSpeed, 1, m_slitherSpeed);

    // m_pDrive->SetLookingColorV(OldCameraVision::RED_CONE_A);
    // m_pDrive->AlignWithVision(1.0, 30, true, false);
    // m_pDrive->ForwardInInchGyro(25, 0.5);
    // //Coming back to start zone 
    // m_pDrive->SetLookingColorV(OldCameraVision::ORANGE_CONE);
    // m_pDrive->AlignWithVision(-1.0, 30, false);
    // m_pDrive->ForwardInInchGyro(25, 0.5);
    // m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_N);
    // m_pDrive->AlignWithVision(0.0, 30, true, false);
    // m_pDrive->ForwardInInchGyro(60, m_slitherSpeed, 1, m_slitherSpeed);
  }

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void BenAutoBarrel::End(bool interrupted) {}

// Returns true when the command should end.
bool BenAutoBarrel::IsFinished() 
{
  return m_isFinished;
}
