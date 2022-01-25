/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/motorcontrol/Spark.h>
#include <frc/motorcontrol/Victor.h>
#include "../ShooterSubsystemBase.h"

class ShooterSubsystemKurgan : public ShooterSubsystemBase
{
public:
  ShooterSubsystemKurgan();

  void SetShootMotor(double speed) override;

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

private:
#ifndef NOHW
  frc::Spark m_shootOne{PWM_SHOOTER_KURGAN_ONE};
  frc::Victor m_shootTwo{PWM_SHOOTER_KURGAN_TWO};
  frc::Victor m_shootThree{PWM_SHOOTER_KURGAN_THREE};
  frc::Victor m_shootFour{PWM_SHOOTER_KURGAN_FOUR};
#endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
