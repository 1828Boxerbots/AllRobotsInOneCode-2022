/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerC418.h"
#include <frc2/command/button/JoystickButton.h>
#include "../include/Drivers/DPDTSwitchDriver.h"
#include <frc/DriverStation.h>
#include "Util.h"
#include <iostream>
#include "../include/Drivers/CameraDrivers/OldCameraVision.h"

SpinSubsystemC418::FMSColors RobotContainerC418::givenColor = SpinSubsystemC418::FMSColors::INVALID;

RobotContainerC418::RobotContainerC418()
{
  m_pMultiplexerDriver = new I2CMultiplexerDriver(I2C_PORT_MULTIPLEXER_C418);

  m_pDrive = new DriveTrainSubsystemC418(m_pMultiplexerDriver);
  m_pLoader = new LoaderSubsystemC418;
  m_pSpin = new SpinSubsystemC418(m_pMultiplexerDriver);
  m_pShooter = new ShooterSubsystemC418;
  m_pArm = new ArmSubsystemC418;

  //Sensors

  //m_pCamera = new CameraSubsystemBase(m_pDrive);

  m_pShootLoad = new ShootLoadCommand(m_pLoader, m_pShooter, m_pDrive, m_encoderSpeedWanted, m_shootSpeed, m_driveSpeed, LIDAR_LOW_C418, LIDAR_HIGH_C418);
  //SpinWithArm Commands
  m_pSpinMotor = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinMotor, m_speed, 0, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pSpinWithColor = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinWithColor, m_speed, m_wantedRotation, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pSpinToColor = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinToColor, m_speed, 0, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pSpinMotorOpp = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinMotor, -m_speed, 0, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pSpinStop = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinStop, m_speed, 0, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pArmDown = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseArm, .6, 0, ArmSubsystemBase::ArmPositions::LOWEST_POS);
  m_pArmUp = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseArm, .6, 0, ArmSubsystemBase::ArmPositions::HIGHEST_POS);
  
  //AutoArm Commands
  m_pAutoArmUp = new AutoArmCommand(m_pArm, m_pSpin, m_pDrive, 0.4, 1 /*1=HIGHEST*/);
  m_pAutoArmDown = new AutoArmCommand(m_pArm, m_pSpin, m_pDrive, 0.4, 2 /*2=LOWEST*/);
  m_pAutoArmSetup = new AutoArmCommand(m_pArm, m_pSpin, m_pDrive, 0.4, 3 /*3=Auto Mode*/);

  m_pAutoLemonPick = new PickUpLemonCommand(m_pLoader, m_pShooter, m_pDrive, 0.2, 0.5);

  m_pAutoLineUp = new AutoLineUpShootCommand(m_pDrive, 40, m_pShooter, m_pLoader);

  m_pGalacticSearchVision = new GalaticPathVision(m_pDrive, m_pLoader);
  m_pNewSlalom = new NewSlalom(m_pDrive);
  m_pBenBarrel = new BenAutoBarrel(m_pDrive);
  m_pNewBounce = new BenAutoBounce(m_pDrive);

  m_pPlayMove = new PlayMove(m_pDrive, PLAY_MOVE_DEFAULT);

  // Configure the button bindings
  ConfigureButtonBindings();
  ConfigureAutonomousCommands();
}

void RobotContainerC418::ConfigureButtonBindings()
{
  //C418

  //Loader
  SetButtonA();
  SetButtonB();
  SetButtonX();
  SetButtonY();

  SetRightBumper();
  SetLeftBumper();

  //Shooter
  SetRightTrigger();
  SetStartButton();
  SetBackButton();
}

void RobotContainerC418::ConfigureAutonomousCommands()
{
  m_pAutoHouse = new frc2::SequentialCommandGroup {
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
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->TurnInDegrees(90); }, {m_pDrive}}
  };

  m_pAutoFollowRed = new frc2::SequentialCommandGroup 
  {
    //frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->Init(); }, {m_pDrive}},
    frc2::RunCommand 
    {
      [this] 
      {
        if(m_pDrive != nullptr)
        {
          m_pDrive->SetLookingColorV(OldCameraVision::FMS_COLOR);
          double centerScreen = 0.0;
          double result = m_pDrive->WhereToTurn(centerScreen, 50);
          Util::Log("Shadow 3", result);
          //camera flips the image
          if(result == 0.0)
          {
            //Stop if object is in center
            m_pDrive->Stop();
          }
          else if(result < -1.0)
          {
            //Turn right if object is not seen
            m_pDrive->TurnRight(0.2);
          }
          else if (result < 0.0)
          {
            //Turn right if object is on the right
            m_pDrive->TurnRight(0.2);
          }
          else if(result > 0.0)
          {
            //Turn left if object is on the left
            m_pDrive->TurnLeft(0.2);
          }
          else
          {
            //Object is in the center
            m_pDrive->Stop();
          }
          //Util::DelayInSeconds(0.2);
        }
      }, {m_pDrive}
    }
  };

  m_pAutoDoLiterallyNothing = new frc2::SequentialCommandGroup 
  {
    //frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->TurnInDegrees(-7, 0.5); }, {m_pDrive}},
    frc2::RunCommand 
    {
      [this] 
      {
        int height;
        int width;
        m_pDrive->GetVisionSize(&height, &width);
        m_pDrive->SetVisionCrop(0, 0, width, height);
        m_pDrive->SetLookingColorV(OldCameraVision::VisionColors::FMS_COLOR);
        m_pDrive->WhereToTurn(0.0, 50);
        Util::Log("Nothere Where", m_pDrive->WhereToTurn(0.0, 50));

        //m_pDrive->ForwardInInchGyro(120, 0.4);
        // m_pDrive->IMUGetAngle();
        // m_pDrive->GetLeftEncoderInch();
        // m_pDrive->GetRightEncoderInch();
      //double lidar = m_pDrive->GetLidarDetectionDistance();
      }
    }
  };

  m_pAutoChallengeOne = new frc2::SequentialCommandGroup
  {
  //  frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->Init(); }, {m_pDrive}},
    //This is the first part of auto challenge one. Going around first cone
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_N); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->AlignWithVision(0.75, 30); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->ForwardInInch(55,0.0,0.4); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->ArcadeVision(0.3, 0.2, OldCameraVision::RED_CONE_N); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->GoAroundCone(true); }, {m_pDrive}},
    //This is the second part of auto challenge one. Going around secondth cone
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->AlignWithVision(-1.0, 50); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->ForwardInInch(100,0.0,0.3); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->ArcadeVision(0.6, -0.2, OldCameraVision::PURPLE_BOTTLE_N); }, {m_pDrive}},
    //This is the third part of auto challenge one. Going around third cone
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->AlignWithVision(-1.0, 50); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->ForwardInInch(100,0.0,0.3); }, {m_pDrive}},
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->ArcadeVision(0.6, -0.2, OldCameraVision::RED_CONE_N); }, {m_pDrive}},
    //This is the last part of the auto challenge one. This is to be in the same position as the starting position
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->ForwardInInch(200,0.0,0.3); }, {m_pDrive}}
  };
  // test 
//   m_pAutoChallengeOne = new frc2::SequentialCommandGroup 
//   {
//     frc2::RunCommand 
//     {
//       [this] 
//       {
//         if(m_pDrive != nullptr)
//         {
//           double centerScreen = -0.75;
//           double result = -79.60;
//           Util::Log("Shadow 2","while result != 0");
// //          while(result != 0.0)
//           {
//             result = m_pDrive->WhereToTurnVision(centerScreen, 50);
//             Util::Log("Shadow", result);
//             //camera flips the image
//             if(result == 0.0)
//             {
//               //Stop if object is in center
//               m_pDrive->Stop();
              
//             }
//             else if(result < -1.0)
//             {
//               //Turn right if object is not seen
//               m_pDrive->TurnRight(0.3);
//             }
//             else if (result < 0.0)
//             {
//               //Turn right if object is on the right
//               m_pDrive->TurnRight(0.3);; ;;
//             }
//             else if(result > 0.0)
//             {
//               //Turn left if object is on the left
//               m_pDrive->TurnLeft(0.2) ; ; ; ;;
//             }
//             else
//             {
//               //Object is in the center
//               m_pDrive->Stop();
//             }
//           }
//           // Util::Log("Shadow 2","Forward in Inch");
//           // m_pDrive->ForwardInInch(0.0,100, .3);

//           // //m_pDrive->TurnInDegrees(-45) 
//           // while(m_pDrive->IMUGetAngle() < 361)
//           // {
//           //   Util::Log("Shadow 2","while IMU-1");
//           //   double rightDistance = m_pDrive->GetDistanceSensorDetectionDistanceRight();
//           //   if (rightDistance < 0.0)
//           //   {
//           //     m_pDrive->TurnRight(0.3);
//           //   }
//           //   else
//           //   {
//           //     m_pDrive->Forward(0.3);
//           //   }
//           //   Util::Log("Shadow 2","while IMU-2");
//           // }
//           m_pDrive->Stop();
//         }
//       }, {m_pDrive}
//     }
//   };

 m_pAutoCircle = new frc2::SequentialCommandGroup 
  {
    frc2::RunCommand 
    {
      [this] 
      {
        if(m_pDrive != nullptr)
        {
          m_pDrive->MoveArcade(0.5,-0.2);
        }
      }, {m_pDrive}
    }
  };

 m_pAutoFetchGyro = new frc2::SequentialCommandGroup 
  {
    frc2::RunCommand 
    {
      [this] 
      {
        if(m_pDrive != nullptr)
        {
          Util::Log("IMU Test", m_pDrive->ReadIMU());
        }
      }, {m_pDrive}
    }
  };


  m_pAutoSlalom = new AutoSlalom(m_pDrive);

  m_pBouncePath = new AutonomousBouncePath(m_pDrive, AutonomousBouncePath::TURN_RADIUS);

  m_pBackupChallengeOne = new BackupChallengeOne(m_pDrive);

  m_pAutoPickUpLemon = new frc2::SequentialCommandGroup 
  {
    //frc2::InstantCommand{[this] {if(m_pDrive != nullptr)    m_pDrive->Init(); }, {m_pDrive}},
    frc2::RunCommand 
    {
      [this] 
      {
        if(m_pDrive != nullptr && m_pLoader != nullptr && m_pShooter != nullptr)
        {
          m_pDrive->SetLookingColorV(OldCameraVision::FMS_COLOR);
          //GetVisionFMS();
          double centerScreen = 0.0;
          double result = m_pDrive->WhereToTurn(centerScreen, 50);
          Util::Log("Lemon result", result);
          Util::Log("Lemon hasBall", m_hasBall);
          //camera flips the image
          if(result == 0.0 || m_hasBall == true)
          {
            //Stop if object is in center
            //m_pDrive->Stop();

            if(m_pDrive->WhereToTurn(centerScreen, 50) > -2.0)
            {
              m_pDrive->MoveTank(0.4, 0.4 * 1.28);
              Util::Log("Lemon State", "MoveTank");
            }
            else if(m_pDrive->WhereToTurn(centerScreen, 50) <= -2.0)
            {
              m_hasBall = true;

              Util::Log("Lemon State", "Before Delay");
              Util::DelayInSeconds(0.3_s);
              Util::Log("Lemon State", "After Delay");
              m_pDrive->Stop();

              m_pLoader->SetLoadMotor();
              Util::Log("Lemon State", "Loading");
              if(m_pLoader->GetPhotogate())
              {
                m_pLoader->Stop();
                Util::Log("Lemon State", "Stopped Loading");
              }
              // m_pLoader->LoadToPhoto();
              // m_pLoader->Stop();

              // m_pShooter->SetShootMotor(1);
              // Util::DelayInSeconds(0.5);
              // m_pLoader->SetLoadMotor(.5);
              // Util::DelayInSeconds(0.1);
              // m_pLoader->Stop();
              // m_pShooter->Stop();
            }
          }
          else if(result < -2.0)
          {
            //Turn right if object is not seen
            m_pDrive->TurnRight(0.3);
            Util::Log("Lemon State", "Turn Right 1");
          }
          else if (result < 0.0)
          {
            //Turn right if object is on the right
            m_pDrive->TurnRight(0.3);
            Util::Log("Lemon State", "Turn Right 2");
          }
          else if(result > 0.0)
          {
            //Turn left if object is on the left
            m_pDrive->TurnLeft(0.2);
            Util::Log("Lemon State", "Turn Left");
          }
          else
          {
            //Object is in the center
            m_pDrive->Stop();
            Util::Log("Lemon State", "Else Stop");
          }
        }
      }, {m_pDrive, m_pLoader, m_pShooter}
    }
  };
}

int RobotContainerC418::ReadDioSwitch()
{
  //Object hooked up to double pole double throw switch driver {Channel A, Channel B}
  /*
  //Uncomment these two lines out to enable DioSwitch
  DPDTSwitchDriver dpdtSwitch{2,3};
  return dpdtSwitch.Get();
  */
  int changeOneTwoThree = 1;
  return changeOneTwoThree;
}
// int RobotContainerC418::ReadDioSwitch()
// {
//   //Object hooked up to double pole double throw switch driver {Channel A, Channel B}
//   /*
//   //Uncomment these two lines out to enable DioSwitch
//   DPDTSwitchDriver dpdtSwitch{2,3};
//   return dpdtSwitch.Get();
//   */
//   int changeOneTwoThree = 1;
//   return changeOneTwoThree;
// }

frc2::Command *RobotContainerC418::GetAutonomousCommand()
{
  /*
  int dioAutoSwitcher;
  dioAutoSwitcher = ReadDioSwitch();
  frc::SmartDashboard::PutBoolean("Case 1", false);
  frc::SmartDashboard::PutBoolean("Case 2", false);
  frc::SmartDashboard::PutBoolean("Case 3", false);
  frc::SmartDashboard::PutBoolean("Case Default", false);
  switch (dioAutoSwitcher)
  {
  case 1:
    frc::SmartDashboard::PutBoolean("Case 1", true);
    return &m_autoInFrontTargetZone;
    break;

  case 2:
    frc::SmartDashboard::PutBoolean("Case 2", true);
    return &m_autoBetweenTargetZoneLoadingZone;
  case 3:
    frc::SmartDashboard::PutBoolean("Case 3", true);
    return &m_autoInFrontLoadingZone;
    break;
  default:
    frc::SmartDashboard::PutBoolean("Case Default", true);
    //return &m_autoInFrontTargetZone;
    break;
  }
  return nullptr;
  

  Util::Log("Shadow 2", "m_pAutoFollowRed");
  if(m_pAutoChallengeOne != nullptr)
  {
    Util::Log("Shadow 3", "m_pAutoFollowRed is NOT null");
    return m_pAutoChallengeOne;
  }
  else
  {
    Util::Log("Shadow 3", "m_pAutoFollowRed is null");
    return nullptr;
  }
  */
  int cases = 5;
  Util::Log("AutoC418", cases);
  switch(cases)
  {
    case 0:
      return m_pAutoSlalom;
      break;
    case 1:
    //  return m_pAutoChallengeOne;
      break;
    case 2:
      return m_pAutoLemonPick;
      break;
    case 3:
      return m_pBouncePath;
      break;
    case 4:
      return m_pAutoFollowRed;
      break;
    case 5:
      return m_pAutoDoLiterallyNothing;
      break;
    case 6:
      return m_pBackupChallengeOne;
      break;
    case 7:
      return m_pAutoFetchGyro;
      break;
    case 8:
      return m_pPlayMove;
      break;
    case 9:
      return m_pNewSlalom;
      break;
    case 10:
      return m_pBenBarrel;
      break;
    case 11:
      return m_pNewBounce;
      break;
    case 12:
      return m_pGalacticSearchVision;
      break;
    case 13:
      return m_pAutoLineUp;
      break;
    default:
      return nullptr;
  }
}

void RobotContainerC418::Init()
{

  if (m_pSpin != nullptr)
    m_pSpin->InterpretFMS(ReadFMS());
  m_pDrive->Init();
  SetDrive(RC_STYLE);
  if (m_pLoader != nullptr)
    m_pLoader->SetLoadMotor(0.0);
  m_pLoader->Init();
  frc::SmartDashboard::PutBoolean("Is Enabled", true);
  m_pShooter->Init();
  
}

void RobotContainerC418::DisableInit()
{
  if (m_pLoader != nullptr)
    m_pLoader->SetLoadMotor(0.0);
  m_pShooter->Init();
  frc::SmartDashboard::PutBoolean("Is Enabled", false);
} 

void RobotContainerC418::SetButtonA()
{
  frc2::Button buttonAOne{[this] { return m_controller.GetAButton(); }};
  buttonAOne.WhileHeld(&m_loaderFeed);
  buttonAOne.WhenReleased(&m_loaderFeedStop);

  frc2::Button buttonATwo{[this] { return m_controller2.GetAButton(); }};
  //buttonATwo.ToggleWhenPressed(m_pAutoArmSetup);
  buttonATwo.ToggleWhenPressed(m_pAutoArmUp);
}

void RobotContainerC418::SetButtonB()
{
  frc2::Button buttonBOne{[this] { return m_controller.GetBButton(); }};
  buttonBOne.WhenHeld(&m_loaderAllIntake);
  buttonBOne.WhenReleased(&m_loaderAllStop);

  frc2::Button buttonBTwo{[this] { return m_controller2.GetBButton(); }};
  buttonBTwo.ToggleWhenPressed(m_pAutoArmDown);
}

void RobotContainerC418::SetButtonX()
{
  frc2::Button buttonXOne{[this] { return m_controller.GetXButton(); }};
  buttonXOne.WhenHeld(&m_loaderMiddle);
  buttonXOne.WhenReleased(&m_loaderMiddleStop);

  frc2::Button buttonXTwo{[this] { return m_controller2.GetXButton(); }};
  buttonXTwo.WhenPressed(m_pSpinMotor);
  //buttonXTwo.WhileHeld(m_pSpinMotor);
  //buttonXTwo.WhenHeld(m_pSpinMotor);

  buttonXTwo.WhenReleased(m_pSpinStop);
}

void RobotContainerC418::SetButtonY()
{
  frc2::Button buttonYOne{[this] { return m_controller.GetYButton(); }};
  buttonYOne.WhenHeld(&m_loaderTop);
  buttonYOne.WhenReleased(&m_loaderTopStop);

  frc2::Button buttonYTwo{[this] { return m_controller2.GetYButton(); }};
  buttonYTwo.WhenPressed(m_pSpinMotorOpp);
  //buttonYOne.WhileHeld(m_pSpinMotorOpp);
  //buttonYTwo.WhenHeld(m_pSpinMotorOpp);

  buttonYTwo.WhenReleased(m_pSpinStop);
}

void RobotContainerC418::SetRightTrigger()
{
  frc2::Button buttonRTOne{[this] { return m_controller.GetRightTriggerAxis(); }};
  buttonRTOne.WhenPressed(&m_shooterSpin);
  buttonRTOne.WhenReleased(&m_shooterStop);
  //m_shooterSpin;

  frc2::Button buttonRTTwo{[this] { return m_controller2.GetRightTriggerAxis(); }};
  buttonRTTwo.WhenPressed(m_pSpinToColor);
}

void RobotContainerC418::SetLeftBumper()
{
  frc2::Button buttonLBOne{[this] {return m_controller.GetLeftBumper(); }};
  buttonLBOne.WhenHeld(&m_loaderAllIntake);
  buttonLBOne.WhenReleased(&m_loaderAllStop);
  // frc2::Button buttonLBOne{[this] { return m_controller.GetBumper(frc::GenericHID::kLeftHand); }};
  // buttonLBOne.WhenPressed(&m_shooterEncoderReset);
  // buttonLBOne.WhenReleased(&m_shooterEncoderReset);

  // frc2::Button buttonLBTwo{[this] { return m_controller2.GetBumper(frc::GenericHID::kLeftHand); }};
  // buttonLBTwo.WhenPressed(m_pShootLoad);
}

void RobotContainerC418::SetRightBumper()
{
  frc2::Button buttonRBOne{[this] { return m_controller.GetRightBumper(); }};
  buttonRBOne.WhenHeld(&m_loaderSetInverted);
  buttonRBOne.WhenReleased(&m_loaderResetInverted);

  frc2::Button buttonRBTwo{[this] { return m_controller2.GetRightBumper(); }};
  buttonRBTwo.WhenHeld(&m_loaderPhotogate);
  buttonRBTwo.WhenReleased(&m_loaderAllStop);
}

void RobotContainerC418::SetStartButton()
{
  frc2::Button startButtonOne{[this] { return m_controller.GetStartButton(); }};
  startButtonOne.WhenPressed(&m_shooterSpinMax);
  startButtonOne.WhenReleased(&m_shooterStop);

  frc2::Button startButttonTwo{[this] { return m_controller2.GetStartButton(); }};
  startButttonTwo.WhenPressed(&m_armLift_Motor);
  startButttonTwo.WhenReleased(&m_armStop);
}

void RobotContainerC418::SetBackButton()
{
  frc2::Button backButtonOne{[this] { return m_controller.GetBackButton(); }};

  backButtonOne.WhenPressed(&m_shooterSpinHalf);
  backButtonOne.WhenReleased(&m_shooterStop);
  //backButton.WhenPressed(m_pShootLoad);

  frc2::Button backButttonTwo{[this] { return m_controller2.GetBackButton(); }};
  backButttonTwo.WhenPressed(&m_armLower_Motor);
  backButttonTwo.WhenReleased(&m_armStop);
}

void RobotContainerC418::GetVisionFMS()
{
  std::string gameData;
  gameData = frc::DriverStation::GetGameSpecificMessage();
  Util::Log("AutoFMS", "GetVisionFMS Start");
  if (gameData.length() > 0)
  {
    switch (gameData[0])
    {
      //Red
    case 'R':
      //case for red cone
      if(gameData.length() > 1)
      {
        switch(gameData[1])
        {
          case 'M':
            m_pDrive->SetVisionFMSColor(OldCameraVision::RED_CONE_M);
            Util::Log("AutoFMS", "Vision Red Morning");
            break;
          case 'A':
            m_pDrive->SetVisionFMSColor(OldCameraVision::RED_CONE_A);
            Util::Log("AutoFMS", "Vision Red Afternoon");
            break;
          case 'N':
            m_pDrive->SetVisionFMSColor(OldCameraVision::RED_CONE_N);
            Util::Log("AutoFMS", "Vision Red Night");
            break;
          case 'G':
            m_pDrive->SetVisionFMSColor(OldCameraVision::REF_GREEN);
            Util::Log("AutoFMS", "Reflective Green");
            break;
        }
      }
      else
      {
        m_pDrive->SetVisionFMSColor(OldCameraVision::RED_CONE_N);
        Util::Log("AutoFMS", "Vision Red Night");
      }
      break;

      //Green
    case 'G':
      //Case for GreenCone
      if(gameData.length() > 1)
      {
         switch(gameData[1])
        {
          case 'M':
            m_pDrive->SetVisionFMSColor(OldCameraVision::GREEN_CONE_M);
            Util::Log("AutoFMS", "Vision Green Morning");
            break;
          case 'A':
            m_pDrive->SetVisionFMSColor(OldCameraVision::GREEN_CONE_A);
            Util::Log("AutoFMS", "Vision Green Afternoon");
            break;
          case 'N':
            m_pDrive->SetVisionFMSColor(OldCameraVision::GREEN_CONE_N);
            Util::Log("AutoFMS", "Vision Green Night");
            break;
        }
      }
      else
      {
        m_pDrive->SetVisionFMSColor(OldCameraVision::GREEN_CONE_N);
        Util::Log("AutoFMS", "Vision Green Night");
      }
      break;

      //Lemon
    case 'L':
      //Case Yellow LEMON
      if(gameData.length() > 1)
      {
         switch(gameData[1])
        {
          case 'M':
            m_pDrive->SetVisionFMSColor(OldCameraVision::YELLOW_LEMON_M);
            Util::Log("AutoFMS", "Vision Lemon Morning");
            break;
          case 'A':
            m_pDrive->SetVisionFMSColor(OldCameraVision::YELLOW_LEMON_A);
            Util::Log("AutoFMS", "Vision Lemon Afternoon");
            break;
          case 'N':
            m_pDrive->SetVisionFMSColor(OldCameraVision::YELLOW_LEMON_N);
            Util::Log("AutoFMS", "Vision Lemon Night");
            break;
        }
      }
      else
      {
        m_pDrive->SetVisionFMSColor(OldCameraVision::YELLOW_LEMON_N);
        Util::Log("AutoFMS", "Vision Lemon Night");
      }
      break;

      //Purple
    case 'P':
      //Case Purple Bottle
      if(gameData.length() > 1)
      {
         switch(gameData[1])
        {
          case 'M':
            m_pDrive->SetVisionFMSColor(OldCameraVision::PURPLE_BOTTLE_M);
            Util::Log("AutoFMS", "Vision Purple Bottle Morning");
            break;
          case 'A':
            m_pDrive->SetVisionFMSColor(OldCameraVision::PURPLE_BOTTLE_A);
            Util::Log("AutoFMS", "Vision Purple Bottle Afternoon");
            break;
          case 'N':
            m_pDrive->SetVisionFMSColor(OldCameraVision::PURPLE_BOTTLE_N);
            Util::Log("AutoFMS", "Vision Purple Bottle Night");
            break;
        }
      }
      else
      {
        m_pDrive->SetVisionFMSColor(OldCameraVision::PURPLE_BOTTLE_N);
        Util::Log("AutoFMS", "Vision Purple Bottle Night");
      }

      break;

      //Other
    case 'Y':
      //Case for YellowCone
      m_pDrive->SetVisionFMSColor(OldCameraVision::YELLOW_CONE);
      Util::Log("AutoFMS", "Vision Yellow Cone");
      break;
    case 'O':
      //Case for Orange Cone
      m_pDrive->SetVisionFMSColor(OldCameraVision::ORANGE_CONE);
      Util::Log("AutoFMS", "Vision Orange");
      break;
    case 'V':
      //Case for Vision Sliders
      Util::Log("AutoFMS", "Vision Slider");
      BreakFMSStr(gameData);
      break;
    case 'C':
      if(gameData.length() > 1)
      {
        if(gameData[1] == 'S')
        {
          m_pDrive->SetContSave();
        }
        else
        {
          BreakContourStr(gameData);
        }
      }
      Util::Log("AutoFMS", "Contour Slider");
      break;
    default:
      //This is corrupt data
      Util::Log("AutoFMS", gameData);
      break;
    }
  }
  else
  { /*Code for no data received yet*/
    Util::Log("AutoFMS", "Error no data recieved");
  }

}

void RobotContainerC418::BreakFMSStr(std::string gameData)
{
  //int charLength = gameData.length()+1;
  char copy[60]; // Variable length arrays are bad! Must be a preset value. 60 is plenty big enough for our purposes.
  strcpy(copy, gameData.c_str());
  char *output = strtok(copy, "-");
  for (int num=0; output != nullptr; num++)
  {
    int value = atoi(output);
    switch (num)
    {
      case 0:
        break;
      case 1:
        m_pDrive->SetHSVLow(1, value);
        break;
      case 2:
        m_pDrive->SetHSVHigh(1, value);
        break;
      case 3:
        m_pDrive->SetHSVLow(2, value);
        break;
      case 4:
        m_pDrive->SetHSVHigh(2, value);
        break;
      case 5:
        m_pDrive->SetHSVLow(3, value);
        break;
      case 6:
        m_pDrive->SetHSVHigh(3, value);
        break;
      default:
        //IT BROKE or there is more when there isnt suppose to be
        break;
    } // end SWITCH
    output = strtok(nullptr, "-");
  } // end FOR
    Util::Log("AutoFMS", "Vision HSV values added");
}

void RobotContainerC418::BreakContourStr(std::string gameData)
{
  char copy[60]; // Variable length arrays are bad! Must be a preset value. 60 is plenty big enough for our purposes.
  strcpy(copy, gameData.c_str());
  char *output = strtok(copy, "-");
  for (int num=0; output != nullptr; num++)
  {
    float value = atof(output);
    switch (num)
    {
      case 0:
        break;
      case 1:
        m_pDrive->SetContArea(true, (double)value);
        break;
      case 2:
        m_pDrive->SetContArea(false, (double)value);
        break;
      case 3:
        m_pDrive->SetContRatio(true, (double)value);
        break;
      case 4:
        m_pDrive->SetContRatio(false, (double)value);
        break;
      case 5:
        m_pDrive->SetContSolid(true, (double)value);
        break;
      case 6:
        m_pDrive->SetContSolid(false, (double)value);
        break;
      default:
        //IT BROKE or there is more when there isnt suppose to be
        break;
    } // end SWITCH
    output = strtok(nullptr, "-");
  } // end FOR
    Util::Log("AutoFMS", "Contour variable checks changed");
}

void RobotContainerC418::AutonomousPeriodic() 
{
  GetVisionFMS();
}

void RobotContainerC418::TeleopPeriodic()
{
#ifndef NOHW
  //GetVisionFMS();
  //m_pDrive->WhereToTurn();
//Reading all Mux Sensors for testing purposes
#ifdef M_DISTANCE_LEFT
  m_pDrive->GetDistanceSensorDetectionDistanceLeft(); //Left Distance Sensor
#endif
#ifdef M_DISTANCE_RIGHT
  m_pDrive->GetDistanceSensorDetectionDistanceRight(); //Right Distance Sensor
#endif

#ifdef M_COLOR
  m_pSpin->GetColor(); //Color Sensor
  Util::DelayInSeconds(1_s);
#endif
#ifdef M_LIDAR
  m_pDrive->GetLidarDetectionDistance(); //Lidar Sensor
  //Util::DelayInSeconds(1);
#endif
#endif
}
