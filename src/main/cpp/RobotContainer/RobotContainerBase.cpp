/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerBase.h"
#include <frc2/command/button/Button.h>

RobotContainerBase::RobotContainerBase() {}

/*
void RobotContainerBase::SetCamerastream()
{
    

    frc::SmartDashboard::PutString("test","After set default");
}
*/

void RobotContainerBase::SetDrive(DriveStyles driveStyle)
{
    //Sets anticollision on or off for teleop, kinda experimental, not really made for games, mainly just for autonomous
    m_pDrive->EnableAnticollision(false);
    switch (driveStyle)
    {
    case TANK_STYLE:
        m_pDrive->SetDefaultCommand(frc2::RunCommand(
            [this] {
                double leftHand = -m_controller.GetLeftY();
                //leftHand = (leftHand/(abs(leftHand)))*(pow(leftHand, 2)); //Square it but maintain the sign
                leftHand = pow(leftHand, 3);
                double rightHand = -m_controller.GetRightY();
                //rightHand = (rightHand/(abs(rightHand)))*(pow(rightHand, 2)); //Square it but maintain the sign
                rightHand = pow(rightHand, 3);
                m_pDrive->MoveTank(leftHand, rightHand);

                Util::Log("SetDrive Left Stick", leftHand);
                Util::Log("SetDrive Right Stick", rightHand);
                Util::Log("SetDrive Left Motor", m_pDrive->GetMotorL());
                Util::Log("SetDrive Right Motor", m_pDrive->GetMotorR());
            },
            {m_pDrive}));
        break;

    case ARCADE_STYLE:
        m_pDrive->SetDefaultCommand(frc2::RunCommand(
            [this] {
                double leftHand = -m_controller.GetLeftY();
                double rightHand = m_controller.GetLeftX();
                Util::Log("SetDrive Left Stick", leftHand);
                Util::Log("SetDrive Right Stick", rightHand);
                Util::Log("SetDrive Left Motor", m_pDrive->GetMotorL());
                Util::Log("SetDrive Right Motor", m_pDrive->GetMotorR());
                m_pDrive->MoveArcade(leftHand, rightHand);
            },
            {m_pDrive}));
        break;
    
    case RC_STYLE:
        m_pDrive->SetDefaultCommand(frc2::RunCommand(
            [this] {
                double leftHand = -m_controller.GetLeftY();
                double rightHand = m_controller.GetRightX();
                //rightHand = rightHand * 0.37;
                Util::Log("SetDrive Left Stick", leftHand);
                Util::Log("SetDrive Right Stick", rightHand);
                Util::Log("SetDrive Left Motor", m_pDrive->GetMotorL());
                Util::Log("SetDrive Right Motor", m_pDrive->GetMotorR());
                m_pDrive->MoveArcade(leftHand, rightHand);
            },
            {m_pDrive}));
        break;
    case RECORD_RC:
        if(m_pRecordMove == nullptr)
        {
            m_pRecordMove = new RecordMove(m_pDrive, &m_controller);
        }
        m_pDrive->SetDefaultCommand(*m_pRecordMove);
        break;
    }
}

void RobotContainerBase::SetButtonA()
{
    frc2::Button buttonA{[this] { return m_controller.GetAButton(); }};
    buttonA.WhileHeld(&m_turretTurnLeft);
    buttonA.WhenReleased(&m_turretStop);
}

void RobotContainerBase::SetButtonB()
{
    frc2::Button buttonB{[this] { return m_controller.GetBButton(); }};
    buttonB.WhenHeld(&m_turretTurnRight);
    buttonB.WhenReleased(&m_turretStop);
}

void RobotContainerBase::SetButtonX()
{
    frc2::Button buttonX{[this] { return m_controller.GetXButton(); }};
    buttonX.WhenHeld(&m_loaderEject);
    buttonX.WhenReleased(&m_loaderStop);
}

void RobotContainerBase::SetButtonY()
{
    frc2::Button buttonY{[this] { return m_controller.GetYButton(); }};
    buttonY.WhenHeld(&m_loaderLoad);
    buttonY.WhenReleased(&m_loaderStop);
}

void RobotContainerBase::SetStartButton()
{
    /*
    frc2::Button startButton{[this] {return m_controller.GetStartButton();}};
    startButton.WhenPressed(&m_follower);
    */
}

void RobotContainerBase::SetBackButton()
{
}

void RobotContainerBase::SetLeftBumper()
{
    frc2::Button bumperL{[this] { return m_controller.GetLeftBumper(); }};
    // Set the bottom back to eject eventually maybe
    bumperL.WhenHeld(&m_shooterSpin);
    bumperL.WhenReleased(&m_shooterStop);
}

void RobotContainerBase::SetRightBumper()
{
    frc2::Button bumperR{[this] { return m_controller.GetRightBumper(); }};
    bumperR.WhenHeld(&m_shooterEject);
    bumperR.WhenReleased(&m_shooterStop);
}

void RobotContainerBase::SetLeftTrigger()
{
    //frc2::Button leftTrigger{[this] {return m_controller.GetTriggerAxis(frc::GenericHID::kLeftHand);}};
    //leftTrigger.WhenPressed(&m_resetEncoder);
}

void RobotContainerBase::SetRightTrigger()
{
}
