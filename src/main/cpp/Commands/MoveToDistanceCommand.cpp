/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/MoveToDistanceCommand.h"

MoveToDistanceCommand::MoveToDistanceCommand(DriveTrainSubsystemBase *pDrive, double targetDistance, double speed)
{
  m_pDrive = pDrive;
  m_targetDistance = targetDistance;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void MoveToDistanceCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void MoveToDistanceCommand::Execute()
{
  double lowTolerance = m_targetDistance - m_toleranceValue;
  double highTolerance = m_targetDistance + m_toleranceValue;
  double currentDistance = m_pDrive->GetLidarDetectionDistance();
  while (currentDistance < lowTolerance || currentDistance > highTolerance)
  {
    if (currentDistance < lowTolerance)
    {
      m_pDrive->MoveTank(-1.0, -1.0);
    }
    else if (currentDistance > highTolerance)
    {
      m_pDrive->MoveTank(1.0, 1.0);
    }
    currentDistance = m_pDrive->GetLidarDetectionDistance();
  }

  m_pDrive->Stop();
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void MoveToDistanceCommand::End(bool interrupted)
{
  m_pDrive->Stop();
}

// Returns true when the command should end.
bool MoveToDistanceCommand::IsFinished()
{
  return false;
}
