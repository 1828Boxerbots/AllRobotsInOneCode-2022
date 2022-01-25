/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerLipALoop.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerLipALoop::RobotContainerLipALoop()
{
  m_pDrive = new DriveTrainSubsystemLipALoop;

  m_pArm = new ArmSubsystemLipALoop;
  m_pWrist = new WristSubsystemLipALoop;
  m_pHand = new HandSubsystemLipALoop;

  m_pPlayMove = new PlayMove(m_pDrive, PLAY_MOVE);

  // Configure the button bindings
  ConfigureButtonBindings();
  m_pDrive->Init();
  //NetworkTable::Initialize();
  //netw = NetworkTable::GetTable("SmartDashboard");
  //m_pCamera->Init();
  SetDrive(RECORD_RC);
}

void RobotContainerLipALoop::ConfigureButtonBindings()
{

  SetRightBumper();
  SetLeftBumper();

  SetButtonA();
  SetButtonB();

  SetButtonX();
  SetButtonY();
}

frc2::Command *RobotContainerLipALoop::GetAutonomousCommand()
{
  // An example command will be run in autonomous
  return m_pPlayMove;
}

void RobotContainerLipALoop::TeleopPeriodic()
{
  // netw->NetworkTable::PutNumber("Server Var", serverVar);
  // serverVar++;
  // netw->NetworkTable::PutNumber("Client Var", clietVar);
}

void RobotContainerLipALoop::SetRightBumper()
{
  frc2::Button bumperR{[this] { return m_controller.GetRightBumper(); }};
  bumperR.WhenHeld(&m_armDown_Servo);
  bumperR.WhenReleased(&m_armStop);
}

void RobotContainerLipALoop::SetLeftBumper()
{
  frc2::Button bumperL{[this] { return m_controller.GetLeftBumper(); }};
  bumperL.WhenHeld(&m_armUp_Servo);
  bumperL.WhenReleased(&m_armStop);
}

void RobotContainerLipALoop::SetButtonA()
{
  frc2::Button buttonA{[this] { return m_controller.GetAButton(); }};
  buttonA.WhenHeld(&m_wristUp);
  buttonA.WhenReleased(&m_wristStop);
}

void RobotContainerLipALoop::SetButtonB()
{
  frc2::Button buttonB{[this] { return m_controller.GetBButton(); }};
  buttonB.WhenHeld(&m_wristDown);
  buttonB.WhenReleased(&m_wristStop);
}

void RobotContainerLipALoop::SetButtonX()
{
  frc2::Button buttonX{[this] { return m_controller.GetXButton(); }};
  buttonX.WhenHeld(&m_handUp);
  buttonX.WhenReleased(&m_handStop);
}

void RobotContainerLipALoop::SetButtonY()
{
  frc2::Button buttonY{[this] { return m_controller.GetYButton(); }};
  buttonY.WhenHeld(&m_handDown);
  buttonY.WhenReleased(&m_handStop);
}

void RobotContainerLipALoop::SetStartButton()
{
  //frc2::Button startButton{[this] {return m_controller.GetStartButton();}};
  //startButton.WhenPressed(&m_follower);
}
