/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/C418/DriveTrainSubsystemC418.h"
#include "subsystems/C418/LoaderSubsystemC418.h"
#include "subsystems/C418/ShooterSubsystemC418.h"
#include "subsystems/C418/SpinSubsystemC418.h"
#include "subsystems/C418/ArmSubsystemC418.h"
#include "subsystems/CameraSubsystemBase.h"
#include "RobotContainerBase.h"
#include "../Commands/ShootLoadCommand.h"
#include "../Commands/SpinWithArm.h"
#include "subsystems/SpinSubsystemBase.h"
#include "../Commands/AutoArmCommand.h"
#include "Commands/AutoSlalom.h"
#include "Commands/AutonomousBouncePath.h"
#include "Commands/PickUpLemonCommand.h"
#include "Commands/BackupChallengeOne.h"
#include "Commands/GalacticSearch/GalaticPathVision.h"
#include "Commands/PlayMove.h"
#include "Commands/NewSlalom.h"
#include "Commands/BenAutoBarrel.h"
#include "Commands/BenAutoBounce.h"
#include "Commands/AutoLineUpShootCommand.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerC418 : public RobotContainerBase
{
public:
  RobotContainerC418();

  void Init() override;
  void DisableInit() override;
  void TeleopPeriodic() override;
  void AutonomousPeriodic() override;

  void SetButtonA() override;
  void SetButtonB() override;
  void SetButtonX() override;
  void SetButtonY() override;
  void SetRightTrigger() override;
  void SetRightBumper() override;
  void SetLeftBumper() override;
  void SetStartButton() override;
  void SetBackButton() override;
  int ReadDioSwitch();

  frc2::Command *GetAutonomousCommand() override;

  void GetVisionFMS() override;
  void BreakFMSStr(std::string gameData) override;
  void BreakContourStr(std::string gameDate);

  static SpinSubsystemC418::FMSColors givenColor;

private:
  //ShootLoadCommand
  ShootLoadCommand *m_pShootLoad = nullptr;
  double m_encoderSpeedWanted = -2000; //REAL ENCODER SPEED = -5500
  double m_driveSpeed = 0.5;
  double m_shootSpeed = 1.0;
  bool m_hasBall = false;

  //SpinWithArm
  SpinWithArm *m_pSpinMotor = nullptr;
  SpinWithArm *m_pSpinWithColor = nullptr;
  SpinWithArm *m_pSpinToColor = nullptr;
  SpinWithArm *m_pSpinMotorOpp = nullptr;
  SpinWithArm *m_pSpinStop = nullptr;
  SpinWithArm *m_pArmUp = nullptr;
  SpinWithArm *m_pArmDown = nullptr;

  //AutoArmCommands
  AutoArmCommand *m_pAutoArmSetup = nullptr;
  AutoArmCommand *m_pAutoArmDown = nullptr;
  AutoArmCommand *m_pAutoArmUp = nullptr;

  PickUpLemonCommand *m_pAutoLemonPick = nullptr;

  // Pulling a pointer variable to access distance sensor driver
  I2CMultiplexerDriver *m_pMultiplexerDriver = nullptr;

  double m_speed = 1.0;
  int m_wantedRotation = 7;
  // The robot's subsystems and commands are defined here...

  void ConfigureButtonBindings();
  void ConfigureAutonomousCommands();

  frc2::SequentialCommandGroup *m_pAutoHouse = nullptr;
  frc2::SequentialCommandGroup *m_pAutoFollowRed = nullptr;
  frc2::SequentialCommandGroup *m_pAutoChallengeOne = nullptr;
  frc2::SequentialCommandGroup *m_pAutoCircle = nullptr;
  frc2::SequentialCommandGroup *m_pAutoDoLiterallyNothing = nullptr;
  frc2::SequentialCommandGroup *m_pGoFullSpeed = nullptr;
  frc2::SequentialCommandGroup *m_pAutoFetchGyro = nullptr;
  frc2::SequentialCommandGroup *m_pAutoPickUpLemon = nullptr;
  
  AutoSlalom *m_pAutoSlalom = nullptr;
  AutonomousBouncePath *m_pBouncePath = nullptr;
  BackupChallengeOne *m_pBackupChallengeOne = nullptr;
  GalaticPathVision *m_pGalacticSearchVision = nullptr;
  AutoLineUpShootCommand *m_pAutoLineUp = nullptr;

  NewSlalom *m_pNewSlalom = nullptr;
  BenAutoBarrel *m_pBenBarrel = nullptr;
  BenAutoBounce *m_pNewBounce = nullptr;

  PlayMove *m_pPlayMove = nullptr;
  const char* PLAY_MOVE_DEFAULT = "/u/c418_recording/recording_2021-03-29_17-07-55.bin";
};
