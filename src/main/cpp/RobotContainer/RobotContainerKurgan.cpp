/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerKurgan.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerKurgan::RobotContainerKurgan()
{
  m_pDrive = new DriveTrainSubsystemKurgan;
  //This is disable due to kurgan broken loader(vail pride day 2/15/20) - Aidan Clark
  m_pLoader = new LoaderSubsystemKurgan;
  m_pShooter = new ShooterSubsystemKurgan;
  // Configure the button bindings
  ConfigureButtonBindings();
  m_pDrive->Init();
  SetDrive(RC_STYLE);
  InitializeAutonomousFunctions();
}

void RobotContainerKurgan::InitializeAutonomousFunctions()
{
  m_pAutoHouse = new frc2::SequentialCommandGroup{
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->Init(); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->EnableAnticollision(true); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->ForwardInSeconds(10); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->TurnInDegrees(45); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->ForwardInSeconds(5); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->TurnInDegrees(90); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->ForwardInSeconds(5); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->TurnInDegrees(45); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->ForwardInSeconds(10); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->TurnInDegrees(90); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->ForwardInSeconds(sqrt(50)); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->TurnInDegrees(90); }, {m_pDrive}}};
}

void RobotContainerKurgan::ConfigureButtonBindings()
{
  //Loader Controlls
  SetButtonA();
  SetButtonB();

  //Shooter Controlls
  //SetLeftBumper();
  //SetRightBumper();
}

frc2::Command *RobotContainerKurgan::GetAutonomousCommand()
{
  return m_pAutoHouse;
}

void RobotContainerKurgan::SetButtonA()
{
  frc2::Button buttonA{[this] { return m_controller.GetAButton(); }};
  buttonA.WhenHeld(&m_loaderEject);
  buttonA.WhenReleased(&m_loaderStop);
}

void RobotContainerKurgan::SetButtonB()
{
  frc2::Button buttonB{[this] { return m_controller.GetBButton(); }};
  buttonB.WhenHeld(&m_loaderLoad);
  buttonB.WhenReleased(&m_loaderStop);
}

void RobotContainerKurgan::TeleopPeriodic()
{
  
}
