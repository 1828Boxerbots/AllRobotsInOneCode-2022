/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/AutoArmCommand.h"

AutoArmCommand::AutoArmCommand(ArmSubsystemBase *pArm, SpinSubsystemBase *pSpin, DriveTrainSubsystemBase *pDrive, double speed, /*ArmSubsystemBase::ArmPositions*/ int wantedPos)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pArm = pArm;
  m_pSpin = pSpin;
  m_pDrive = pDrive;

  AddRequirements(pArm);
  AddRequirements(pSpin);
  AddRequirements(pDrive);
  m_speed = speed;
  m_wantedPos = wantedPos;
}

// Called when the command is initially scheduled.
void AutoArmCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoArmCommand::Execute()
{

  m_pSpin->SetSpinMotor(0.0);

  Util::Log("Auto Arm Stuff", "1");

  switch (m_wantedPos)
  {
  case 1:
    //Checking if arm is already up
    if (m_pArm->GetPosition() == 1)
    {
      m_pArm->StopMotor();
      Util::Log("Auto Arm Stuff", "Up Over");
    }
    else
    {
      //continues going up
      m_pArm->SetMotor(m_speed);
      char str[200];
      sprintf(str, "Up Going %d", upNum);
      Util::Log("Auto Arm Stuff", str);
      upNum++;
    }
    break;

  case 2:
    //Checking if arm is already down
    if (m_pArm->GetPosition() == 0)
    {
      m_pArm->StopMotor();
      Util::Log("Auto Arm Stuff", "Down Over");
    }
    else
    {
      //Continues going down
      m_pArm->SetMotor(-m_speed);
      char str[200];
      sprintf(str, "Down Going %d", downNum);
      Util::Log("Auto Arm Stuff", str);
      downNum++;
    }
    break;

  case 3:
    //Stops spin before raising arm
    //Raises arm automatically
    if (m_pArm->GetPosition() == 1)
    {
      m_pArm->StopMotor();
      Util::Log("Auto Arm Stuff", "Up Over");
      armCheck = 1;
    }

    else
    {
      //continues going up
      m_pArm->SetMotor(m_speed);
      char str[200];
      sprintf(str, "Up Going %d", upNum);
      Util::Log("Auto Arm Stuff", str);
      upNum++;
      //Checks here so that things happend after each other instead of together
      check = 0;
      armCheck = 0;
    }

    if (armCheck == 1)
    {
      //-1 means invalid. All this is doing is making sure that there is color showing up
      if (m_pSpin->ReadColorSensor() != -1)
      {
        //Stops the robot if the color sensor is in range of the wheel
        //m_pDrive->MoveTank(ZERO, ZERO);  //TeleOp Test
        //In the rules, in order to get points, you need to spin the wheel a certain amount of time before
        m_pSpin->SpinNumRotations(/*Speed*/ ROUGHWHEELSPIN, /*Rotations*/ 2);
        //Spins wheel to be on correct color
        m_pSpin->SpinToColor(PRECISECOLORSPIN);
        check = 1;
      }

      else
      {
        //Moves robot to go forwards until color sensor sees color
        m_pDrive->MoveTank(m_speed, m_speed);
      }
      //Made so that once the color wheel is spun to the correct color, the arm will go down
      if (check == 1)
      {

        if (m_pArm->GetPosition() == 0)
        {
          m_pArm->StopMotor();
          Util::Log("Auto Arm Stuff", "Down Over");
        }

        else
        {
          //Continues going down
          m_pArm->SetMotor(-m_speed);
          char str[200];
          sprintf(str, "Down Going %d", downNum);
          Util::Log("Auto Arm Stuff", str);
          downNum++;
        }
      }
    }
    break;

  default:
    m_pArm->StopMotor();
    Util::Log("Auto Arm Stuff", "Failure");
    break;
  }
}

// Called once the command ends or is interrupted.
void AutoArmCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoArmCommand::IsFinished() { return m_isFinished; }
