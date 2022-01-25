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

class HandSubsystemLipALoop : public frc2::SubsystemBase
{
public:
  HandSubsystemLipALoop();

  void ResetToZero();
  void HandMotor(double angle);

  void MoveHandStop();
  void MoveHandOpen();
  void MoveHandClose();
  void Init();
  double GetOneDegree();
  double GetMinLimit();
  double GetMaxLimit();

private:
//object
#ifndef NOHW
  frc::Servo m_handServo{PWM_HANDSERVO_LIPALOOP};
#endif

  //Variables
  double m_oneDegree = 0.005;
  double m_handAngle = 0.0;

  const double HAND_MIN = 0.06;
  const double HAND_MAX = 0.5;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
