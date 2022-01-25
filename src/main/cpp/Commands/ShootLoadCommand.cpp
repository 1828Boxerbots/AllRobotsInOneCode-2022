/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ShootLoadCommand.h"
#include <frc/SmartDashboard/SmartDashboard.h>

ShootLoadCommand::ShootLoadCommand(LoaderSubsystemBase *pLoader, ShooterSubsystemBase *pShooter, DriveTrainSubsystemBase *pDrive, double encoderWanted, double shootSpeed, double driveSpeed, double lidarLow, double lidarHigh)
{
  m_pLoader = pLoader;
  m_pShooter = pShooter;
  m_pDrive = pDrive;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(pLoader);
  AddRequirements(pShooter);
  AddRequirements(pDrive);

  m_encoderWanted = encoderWanted;
  m_shootSpeed = shootSpeed;
  m_driveSpeed = driveSpeed;
  m_lidarLow = lidarLow;
  m_lidarHigh = lidarHigh;
}

// Called when the command is initially scheduled.
void ShootLoadCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void ShootLoadCommand::Execute()
{
  //Loading a ball to be ready to fire
  while (m_pLoader->IsLoaded())
  {
    m_pLoader->SetLoadMotor();
  }

  m_pLoader->SetLoadMotor(0.0);

  //Lidar getting correct distance
  //Too High / Too far
  if (m_pDrive->GetLidarDetectionDistance() > m_lidarHigh)
  {
    m_pDrive->SetMotorL(m_driveSpeed);
    m_pDrive->SetMotorR(m_driveSpeed);
    return;
  }
  //Too Low / Too close
  if (m_pDrive->GetLidarDetectionDistance() < m_lidarLow)
  {
    m_pDrive->SetMotorL(-m_driveSpeed);
    m_pDrive->SetMotorR(-m_driveSpeed);
    return;
  }

  m_pDrive->Stop();

  //Since the speed is negative this is the "largest value"
  double encoderLowTol = m_encoderWanted - m_encoderTolerance;
  //"Smallest Value"
  double encoderHighTol = m_encoderWanted + m_encoderTolerance;
  Util::Log("ShootLoad LowTol", encoderLowTol);
  Util::Log("ShootLoad HighTol", encoderHighTol);

  //Set shooter motor
  if (m_shootSpeed != 0.0)
  {
    Util::Log("motor speed 1", m_shootSpeed);
    m_pShooter->SetShootMotor(m_shootSpeed);
  }
  else
  {
    Util::Log("motor speed 2", 1.0);
    m_pShooter->SetShootMotor(1.0);
  }

  double shooterSpeed = m_pShooter->EncoderSpeed();
  if (shooterSpeed < encoderLowTol || shooterSpeed > encoderHighTol)
  {
    m_pShooter->SetShootMotor(m_shootSpeed);

    shooterSpeed = m_pShooter->EncoderSpeed();

    Util::Log("ShootLoad ShooterSpeed", shooterSpeed);
    return;
  }

  Util::Log("ShootLoad ShooterSpeed", m_shootSpeed);

  Util::DelayInSeconds(0.25_s);

  m_pLoader->Load(1.0);
  Util::DelayInSeconds(m_oneBallTime);
  //m_pLoader->Stop();
  //Not Sure yet if we should have this
  m_pShooter->Stop();
  m_pLoader->SetLoadMotor(0.0, -1);

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void ShootLoadCommand::End(bool interrupted)
{
  m_pLoader->Stop();
  m_pShooter->Stop();
}

// Returns true when the command should end.
bool ShootLoadCommand::IsFinished()
{
  return m_isFinished;
}
