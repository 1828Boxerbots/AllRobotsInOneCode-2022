/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Servo.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "../../Util.h"
#include "../../Constants.h"

class WristSubsystemLipALoop : public frc2::SubsystemBase
{
public:
  WristSubsystemLipALoop();

  void ResetToZero();
  void WristMotor(double angle);
  void MoveWristStop();
  void MoveWristUp();
  void MoveWristDown();
  double GetOneDegree();
  double GetMinLimit();
  double GetMaxLimit();
  void Init();

private:
#ifndef NOHW
  frc::Servo m_wristServo{PWM_WRISTSERVO_LIPALOOP};
#endif

  //Variables
  double m_oneDegree = 0.005;
  double m_wristAngle = 0.0;

  const double WRIST_MIN = 0.0;
  const double WRIST_MAX = 0.5;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
