/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/motorcontrol/Spark.h>
#include "../ShooterSubsystemBase.h"

class ShooterSubsystemRocky : public ShooterSubsystemBase
{
public:
  ShooterSubsystemRocky();

  virtual void SetShootMotor(double speed);
  virtual double GetSetPoint();
  bool AutoShooterRunTime() override;
  void WaitShooter(units::second_t waitTime) override;

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

private:
#ifndef NOHW
  frc::Spark m_shooterMotor{PWM_SHOOTMOTOR_ROCKY};
#endif

public:
  static constexpr double SHOOTER_SPEED_HIGH_TARGET = 1.0;
  static constexpr double SHOOTER_SPEED_LOW_TARGET = 0.5;
  static constexpr double LIDAR_DISTANCE_HIGH_TARGET = 11.0;
  static constexpr double LIDAR_DISTANCE_LOW_TARGET = 5.0;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
