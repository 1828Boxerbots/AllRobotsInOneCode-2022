/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/motorcontrol/Victor.h>
#include "../DriveTrainSubsystemBase.h"

class DriveTrainSubsystemKurgan : public DriveTrainSubsystemBase
{
public:
  DriveTrainSubsystemKurgan();

  void SetMotorL(double speed) override;
  void SetMotorR(double speed) override;
  void Init() override;
  //double WhereToTurnVision(double deadZoneRange = 100.0, double deadZone = 0.0) override;
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

private:
#ifndef NOHW
  frc::Victor m_leftMotor1{PWM_LEFTMOTOR_KURGAN_ONE};
  frc::Victor m_leftMotor2{PWM_LEFTMOTOR_KURGAN_TWO};
  frc::Victor m_rightMotor1{PWM_RIGHTMOTOR_KURGAN_ONE};
  frc::Victor m_rightMotor2{PWM_RIGHTMOTOR_KURGAN_TWO};

  double m_deadZone = 50;
#endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
