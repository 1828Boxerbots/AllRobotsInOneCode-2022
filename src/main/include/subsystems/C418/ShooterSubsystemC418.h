/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../ShooterSubsystemBase.h"
#include <frc/motorcontrol/Victor.h>
#include <frc/Encoder.h>

class ShooterSubsystemC418 : public ShooterSubsystemBase
{
public:
  ShooterSubsystemC418();
  void Init() override;

  void SetShootMotor(double speed) override;
  void ResetEncoder() override;
  double EncoderSpeed() override;

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

private:
#ifndef NOHW
  frc::Victor m_shooterMotor{PWM_SHOOTMOTOR_C418};
  frc::Encoder m_shooterEncoder{DIO_SHOOTER_ENCODER_ONE_C418, DIO_SHOOTER_ENCODER_TWO_C418};
#endif

  const int PULSES_PER_ROTATION = 80;

  frc::Timer m_timer;
  units::second_t m_startTime = 0.0_s;
  double m_encoderRawStart = 0.0;

  double m_motorSpeed = 0.75;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
