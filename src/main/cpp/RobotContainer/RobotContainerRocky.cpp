/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerRocky.h"
#include <frc2/command/button/JoystickButton.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include "../include/Drivers/DPDTSwitchDriver.h"

RobotContainerRocky::RobotContainerRocky()
{
  m_pDrive = new DriveTrainSubsystemRocky;
  m_pTurret = new TurretSubsystemRocky;
  m_pLoader = new LoaderSubsystemRocky;
  m_pShooter = new ShooterSubsystemRocky;
  //m_pCamera = new CameraSubsystemBase(m_pDrive);

  frc::SmartDashboard::PutString("test", "test");

  m_pGalacticSearchVision = new GalaticPathVision(m_pDrive, m_pLoader);

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainerRocky::ConfigureButtonBindings()
{

  // Configure your button bindings here

  SetButtonA();
  SetButtonB();

  SetLeftBumper();
  SetRightBumper();

  SetLeftTrigger();
  SetRightTrigger();

  SetButtonX();
  SetButtonY();

  //Allign Control
  //SetStartButton();
}

int RobotContainerRocky::ReadDioSwitch()
{
  //Object hooked up to double pole double throw switch driver {Channel A, Channel B}
  DPDTSwitchDriver dpdtSwitch{2, 3};
  return dpdtSwitch.Get();
}

frc2::Command *RobotContainerRocky::GetAutonomousCommand()
{
  return m_pGalacticSearchVision;

  // //DIO variable meant to switch the autonomous scenario
  // int dioAutoSwitcher;
  // dioAutoSwitcher = ReadDioSwitch();
  // frc::SmartDashboard::PutBoolean("Case 1", false);
  // frc::SmartDashboard::PutBoolean("Case 2", false);
  // frc::SmartDashboard::PutBoolean("Case 3", false);
  // frc::SmartDashboard::PutBoolean("Case Default", false);
  // switch (dioAutoSwitcher)
  // {
  // case 1:
  //   frc::SmartDashboard::PutBoolean("Case 1", true);
  //   return &m_autoInFrontTargetZone;
  //   break;

  // case 2:
  //   frc::SmartDashboard::PutBoolean("Case 2", true);
  //   return &m_autoBetweenTargetZoneLoadingZone;
  // case 3:
  //   frc::SmartDashboard::PutBoolean("Case 3", true);
  //   return &m_autoInFrontLoadingZone;
  //   break;
  // default:
  //   frc::SmartDashboard::PutBoolean("Case Default", true);
  //   return &m_autoInFrontTargetZone;
  //   break;
  // }
  // return nullptr;
}

void RobotContainerRocky::Init()
{
  m_pDrive->Init();
  m_pShooter->Init();
  SetDrive(RC_STYLE);
}

void RobotContainerRocky::DisableInit()
{
  m_pShooter->DisableInit();
}

void RobotContainerRocky::GetVisionFMS()
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
            m_pDrive->SetVisionFMSColor(OldCameraVision::LEMON_ROCKY_M);
            Util::Log("AutoFMS", "Vision Lemon Morning");
            break;
          case 'A':
            m_pDrive->SetVisionFMSColor(OldCameraVision::LEMON_ROCKY_A);
            Util::Log("AutoFMS", "Vision Lemon Afternoon");
            break;
          case 'N':
            m_pDrive->SetVisionFMSColor(OldCameraVision::LEMON_ROCKY_N);
            Util::Log("AutoFMS", "Vision Lemon Night");
            break;
        }
      }
      else
      {
        m_pDrive->SetVisionFMSColor(OldCameraVision::LEMON_ROCKY_N);
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

void RobotContainerRocky::BreakFMSStr(std::string gameData)
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

void RobotContainerRocky::SetRightTrigger()
{
  frc2::Button buttonRTOne{[this] { return m_controller.GetRightTriggerAxis(); }};
  buttonRTOne.WhenPressed(&m_shooterEject);
  buttonRTOne.WhenReleased(&m_shooterStop);
}

void RobotContainerRocky::SetLeftTrigger()
{
  frc2::Button buttonLTOne{[this] { return m_controller.GetLeftTriggerAxis(); }};
  buttonLTOne.WhenPressed(&m_shooterSpin);
  buttonLTOne.WhenReleased(&m_shooterStop);
}

void RobotContainerRocky::SetLeftBumper()
{
  frc2::Button bumperL{[this] { return m_controller.GetLeftBumper(); }};
  bumperL.WhenHeld(&m_loaderLoad);
  bumperL.WhenReleased(&m_loaderStop);
}

void RobotContainerRocky::SetRightBumper()
{
  frc2::Button bumperR{[this] { return m_controller.GetRightBumper(); }};
  bumperR.WhenHeld(&m_loaderEject);
  bumperR.WhenReleased(&m_loaderStop);
}

void RobotContainerRocky::AutonomousPeriodic() 
{
  GetVisionFMS();
}

void RobotContainerRocky::TeleopPeriodic()
{
#ifndef NOHW
//Reading all Mux Sensors for testing purposes
#ifdef M_DISTANCE_LEFT
  m_pDrive->GetDistanceSensorDetectionDistanceLeft(); //Left Distance Sensor
#endif
#ifdef M_DISTANCE_RIGHT
  m_pDrive->GetDistanceSensorDetectionDistanceRight(); //Right Distance Sensor
#endif

#ifdef M_LIDAR
  m_pDrive->GetLidarDetectionDistance(); //Lidar Sensor
  //Util::DelayInSeconds(1);
#endif
#endif
}
