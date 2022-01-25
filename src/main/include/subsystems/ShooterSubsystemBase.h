/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/Spark.h>
#include "../Util.h"
#include "../Constants.h"

class ShooterSubsystemBase : public frc2::SubsystemBase
{
public:
  ShooterSubsystemBase();

  void Shoot(double shootSpeed);
  void Stop() { Shoot(0.0); }
  void ShootBump(bool bumpL, bool bumpR);
  bool AtSetpoint(double position);
  double GetEncoderSpeed() { return m_speed; }
  virtual double EncoderSpeed() { return -1; }
  virtual void Init() {}
  virtual void DisableInit();
  virtual void SetShootMotor(double speed) {}
  virtual double GetSetPoint() { return 0.0; }
  virtual bool AutoShooterRunTime() { return false; }
  virtual void WaitShooter(units::second_t waitTime) {}
  virtual void ResetEncoder() {}

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  virtual void Periodic();

private:
protected:
  const double SHOOTSPEED = 1.0;
  double m_speed = 0.0;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
