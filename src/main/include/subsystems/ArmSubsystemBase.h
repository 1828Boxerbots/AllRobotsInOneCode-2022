/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Util.h"
#include "Constants.h"

class ArmSubsystemBase : public frc2::SubsystemBase
{
public:
  ArmSubsystemBase();

  enum ArmPositions
  {
    INVALID_POS = -1,
    LOWEST_POS,
    HIGHEST_POS,
    LOWEST_POS_TIME
  };

  void Log(std::string title, double num);
  void Log(std::string title, int num);
  void Log(std::string title, bool flag);
  void Log(std::string title, std::string phrase);

  // Sets arm to a certain position
  // parm1: pos- sets arm to certain position on robot
  //    pos = LOWEST_POS is the lowest
  //    pos = HIGHEST_POS is the highest
  virtual void SetPosition(int pos) {}

  //Get what the current are position is
  // returns LOWEST_POS for lowest position
  //        HIGHEST_POS for highest position
  //      overrides: can return other numbers
  virtual int GetPosition() { return INVALID_POS; }

  // LiftArmUp - incrementally move up by one degree (uses GetOneDegree)
  virtual void LiftArmUp(double scale = 0, double speed = 0.0) {}
  // LiftArmDown - incrementally move down by one degree (uses GetOneDegree)
  virtual void LiftArmDown(double scale = 0, double speed = 0.0) {}
  // resets servo and encoders to zero
  virtual void ResetToZero() {}

  // returns incremental "one degree" value
  virtual double GetOneDegree() { return 1.0; }

  // returns scale factor for motor
  virtual double GetScale() { return 0.0; }

  // returns minimum (lower limit) of arm
  virtual double GetMinLimit() { return 0.0; }

  // returns maximum (upper limit) of arm
  virtual double GetMaxLimit() { return 180.0; }

  // pure virtual function to force child classes to create Init() and DisableInit()
  virtual void Init() = 0;
  virtual void DisableInit() = 0;

  // stops arm motor, no matter where they are (like)
  virtual void StopMotor() { SetMotor(0.0); }

  // limits the armSpeed and calls SetMotor()
  // param1: armSpeed
  void Lift(double armSpeed);
  virtual void LimitedLift(double speed) {}

  // moves arm up at given speed
  // param1: speed=motor speed to raise arm
  virtual void Raise(double speed = 1.0) { SetMotor(speed); }

  // moves arm down at given speed
  // param1: speed=motor speed to raise arm
  virtual void Lower(double speed = 1.0) { SetMotor(-speed); }

  // returns TRUE if upper limit switch is hit (on a raise)
  // uses hardware limit switches
  virtual bool UpperLimitHit() { return false; }

  // returns TRUE if lower limit switch is hit (on a lower)
  // uses hardware limit switches
  virtual bool LowerLimitHit() { return false; }

  // sets hardware motor(s) to given speed.
  // no LIMITs done.  Refer to LimitedLift.
  virtual void SetMotor(double speed = 1.0) {}
  virtual double GetMotor() { return 0.0; }

protected:
  // encoder value or servo angle
  double m_armAngle = 0.0;

  // current lift speed to set motor to (+)raise, (-)lower
  double m_liftSpeed = 1.0;
};