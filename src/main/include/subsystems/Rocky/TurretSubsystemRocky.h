/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/motorcontrol/Spark.h>
#include "../../Util.h"
#include "../../Constants.h"

class TurretSubsystemRocky : public frc2::SubsystemBase
{
public:
  TurretSubsystemRocky();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();
  void Turn(double angle = 0.0);
  void Turn(bool aButton, bool bButton);

  double m_turretAngle = 0.0;

private:
  const double LOWERLIMIT = -50.0;
  const double UPPERLIMIT = 50.0;
  const double MOTORSPEED = 0.5;

#ifndef NOHW
  frc::Spark m_turretMotor{PWM_TURRETMOTOR_ROCKY};
#endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
