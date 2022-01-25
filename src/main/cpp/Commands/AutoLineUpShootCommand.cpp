// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/AutoLineUpShootCommand.h"

AutoLineUpShootCommand::AutoLineUpShootCommand(DriveTrainSubsystemBase *pDrive, double wantedDistance, ShooterSubsystemBase *pShoot, LoaderSubsystemBase *pLoad) 
{
  m_pDrive = pDrive;
  m_pShoot = pShoot;
  m_pLoad = pLoad;
    AddRequirements(m_pDrive);
    AddRequirements(m_pLoad);
    AddRequirements(m_pShoot);
  // Use addRequirements() here to declare subsystem dependencies.
    m_wantedDistance = wantedDistance;
}

// Called when the command is initially scheduled.
void AutoLineUpShootCommand::Initialize() 
{
  m_isFinished = false;
  //int height;
  //int width;
  m_pDrive->SetLookingColorV(OldCameraVision::REF_GREEN);
  //m_pDrive->GetVisionSize(&height, &width);
  //m_pDrive->SetVisionCrop(0, height*0.75, width, height*0.25);
}

// Called repeatedly when this Command is scheduled to run
void AutoLineUpShootCommand::Execute() 
{
  if(m_isFinished == false)
  {
    m_pDrive->AlignWithVision(0.0, 7, true, false);
    m_pDrive->SetMotorL(0.1);
    m_pDrive->SetMotorR(0.1);
    //m_pDrive->PrecisionMovementLidar(30, 0.4);
    //ForwardLidarGyro(70, 0.1);
    // m_pLoad->PhotogateStop();
    // m_pShoot->Shoot(-0.73);
    // Util::DelayInSeconds(2.5);
    // for(int i = 0; i < 3; i++)
    // {
    //   m_pLoad->PhotogateStop();
    //   m_pLoad->SetLoadMotor(0.5);
    //   Util::DelayInSeconds(.8);
    // }
    // m_pLoad->Stop();
    // m_pShoot->Stop();
    m_isFinished = true;
  }

}

void AutoLineUpShootCommand::ForwardLidarGyro(double wantedDistance, double speed)
{
  double deadZoneLidar = 5.0;
  double deadZoneIMU = 1;
  double currentDistance = m_pDrive->GetLidarDetectionDistance();
  Util::Log("Lidar", "Activated");
  if(currentDistance < 0) {  Util::Log("Lidar","No See");  }
  
  double startIMU = m_pDrive->IMUGetAngle();
  double highIMU, lowIMU;
  double x, y;

  while (currentDistance < (wantedDistance - deadZoneLidar) || currentDistance > (wantedDistance + deadZoneLidar))
  {
    highIMU = startIMU + deadZoneIMU;
    lowIMU = startIMU - deadZoneIMU;
    
    if (currentDistance < (wantedDistance - deadZoneLidar) )
    {
      if(m_pDrive->IMUGetAngle() > highIMU)
      {
        x = -speed/4;
      }
      else if(m_pDrive->IMUGetAngle() < lowIMU)
      {
        x = speed/4;
      }
      y = -speed;
    }
    if (currentDistance > wantedDistance + deadZoneLidar)
    {
      if(m_pDrive->IMUGetAngle() > highIMU)
      {
        x = speed/4;
      }
      else if(m_pDrive->IMUGetAngle() < lowIMU)
      {
        x = -speed/4;
      }
      y = speed;
    }

    m_pDrive->MoveArcade(y, x);
    currentDistance = m_pDrive->GetLidarDetectionDistance();
    Util::Log("LidarDistance", currentDistance);
  }

  m_pDrive->Stop();
}

// Called once the command ends or is interrupted.
void AutoLineUpShootCommand::End(bool interrupted) 
{
  //m_pShoot->Shoot(0.0);
}

// Returns true when the command should end.
bool AutoLineUpShootCommand::IsFinished() 
{
  return m_isFinished;
}
