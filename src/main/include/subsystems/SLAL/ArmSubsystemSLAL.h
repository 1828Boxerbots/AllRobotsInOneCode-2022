/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../ArmSubsystemBase.h"
#include <frc/motorcontrol/Talon.h>
#include <frc/DigitalInput.h>

class ArmSubsystemSLAL : public ArmSubsystemBase
{
public:
  ArmSubsystemSLAL();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  virtual void SetMotor(double speed);
  virtual double GetMotor();
  //void SwitchCheck(bool bumperL, bool bumperR);
  virtual bool UpperLimitHit();
  virtual bool LowerLimitHit();
  void Init() override {}
  void DisableInit() override {}
  virtual void SetPosition(int pos);
  virtual int GetPosition();
  virtual void Raise(double speed = 1.0);
  virtual void Lower(double speed = 1.0);

private:
#ifndef NOHW
  frc::Talon m_liftMotorOne{PWM_ARM_SLAL_ONE};
  frc::Talon m_liftMotorTwo{PWM_ARM_SLAL_TWO};
  frc::DigitalInput m_topSwitch{DIO_TOPSWITCH_SLAL};
  frc::DigitalInput m_bottomSwitch{DIO_BOTTOMSWITCH_SLAL};
#endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
