/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/MoveTankCommand.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
MoveTankCommand::MoveTankCommand(DriveTrainSubsystemBase *pDrive, double left, double right)
{
  m_pDrive = pDrive;
  m_left = left;
  m_right = right;

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void MoveTankCommand::Initialize()
{
}

void MoveTankCommand::Execute()
{
  if (m_pDrive != nullptr)
  {
    m_pDrive->MoveTank(m_left, m_right);
  }
}
