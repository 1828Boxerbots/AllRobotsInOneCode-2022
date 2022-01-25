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
#include <frc/DriverStation.h>
#include <math.h>
#include <frc/Timer.h>
#include "../Util.h"
#include "../Constants.h"
#include "../Drivers/CameraDrivers/OldCameraVision.h"
#include "frc/ADIS16448_IMU.h"

class DriveTrainSubsystemBase : public frc2::SubsystemBase
{
public:
  DriveTrainSubsystemBase();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  virtual void Periodic();
  virtual void MoveTank(double leftY, double rightY);
  virtual void MoveArcade(double Y, double X);
  void ArcadeVision(double y, double x,  OldCameraVision::VisionColors color = OldCameraVision::VisionColors::GREEN_CONE_N);
  void TimedArcade(double y, double x, units::second_t time);
  void IMUArcade(double y, double x, double angle);
  void Stop();
  void Forward(double speed = 1.0);
  void ForwardInInch(double inch, double angle, double speed);
  void LogEncoder();
  bool MoveAlignPID(double targetDistance, double heading, double speed = 1.0);
  void SetCollision(bool colliding = true) { m_isColliding = colliding; }
  void FixRotation(units::degree_t wantedAngle, double speed = 1.0);
  void ForwardInInches2(double inches, double speed);
  virtual double GetPulsesPerRevolution() { return 0.0001; } //Random Small Number
  virtual units::degree_t GyroGetAngle() { return m_gyroAngle; }
  virtual void GyroInit() {}
  virtual void IMUInit() {}
  virtual double IMUGetAngle() { return 1.0; }
  virtual void Init();
  virtual void SetMotorL(double speed) {}
  virtual void SetMotorR(double speed) {}
  virtual double GetMotorL() { return 0; }
  virtual double GetMotorR() { return 0; }
  virtual void TurnLeft(double speed = 1.0);
  virtual void TurnRight(double speed = 1.0);
  virtual double GetLeftEncoderInch() { return -1.0; }
  virtual double GetRightEncoderInch() { return -1.0; }
  virtual double GetLeftEncoderRaw() { return -1.0; }
  virtual double GetRightEncoderRaw() { return -1.0; }
  virtual void ResetEncoder() {}
  virtual void ForwardInSeconds(double goalTime, double speed = 1.0);
  virtual void TurnInDegrees(double relativeAngle, double speed = 0.75, double turnRadius = 11);
  virtual void TurnInDegreesGyro(double relativeAngle, double speed = 0.75);
  virtual void ForwardInInchGyro(double inch, double speed = 1.0, double angleDeadZone = 1, double turnSpeed = 0.05);
  //virtual void DetectionSoftware(double detectionDistance) {}
  virtual double GetLidarDetectionDistance() { return 0.0; }
  virtual double GetDistanceSensorDetectionDistanceLeft() { return 0.0; }
  virtual double GetDistanceSensorDetectionDistanceRight() { return 0.0; }
  virtual void PrecisionMovementLidar(double wantedDistance, double speed) {}
  virtual bool IsDistanceLeftActive() { return false; }
  virtual bool IsDistanceRightActive() { return false; }
  virtual void InitLeft(){};
  virtual void InitRight(){};
  virtual void GoAroundCone(bool turnRight = false){};
  virtual void SetHSVHigh(int HSV, int value) {}
  virtual void SetHSVLow(int HSV, int value) {}
  virtual void SetContArea(bool isLow, double value) {}
  virtual void SetContRatio(bool isLow, double value) {}
  virtual void SetContSolid(bool isLow, double value) {}
  virtual void SetContSave() {}
  virtual void SetVisionFMSColor(OldCameraVision::VisionColors color) {}
  virtual void SetLookingColorV(OldCameraVision::VisionColors color) {}
  virtual OldCameraVision::VisionColors GetLookingColorV() { return OldCameraVision::INVALID_COLOR;}
  virtual double ReadIMU();
  virtual double GetCentroidY() {return -3;}
  virtual double GetCentroidX() {return -3;}
  virtual void SetVisionCrop(int cropX, int cropY, int cropW, int cropH) {}
  virtual void GetVisionSize(int *pHeight, int *pWidth) {}

  // virtual void GetVisionFMS();
  // virtual void BreakFMSStr(std::string gameData);

  virtual void EnableAnticollision(bool enable = true) { m_hasAntiCollision = enable; }

  //Temp Function meant to test turning function
  virtual void ForwardIninchTurn(double inch, double angle, double speed) {}

  void AlignWithVision(double deadZoneLocation = 0.0, int deadZoneRange = 100, bool defaultTurnRight = true, bool forward = true);
  void MoveWithVision(double deadZoneLocation = 0.0, int deadZoneRange = 100, int moveSpeed = 0.5, bool defaultTurnRight = true);
  virtual double WhereToTurn(double deadZoneLocation = 0.0, int deadZoneRange = 100){return 0.0;}

  void RotateToDegreeAbsolute(double degree, double speed, double deadZone);

protected:
  bool m_isColliding = false;

  frc::Timer m_autoTimer;

  double m_leftEncoderSim = 0;
  double m_rightEncoderSim = 0;
  units::degree_t m_gyroAngle = 0.0_deg;
  units::degree_t m_imuAngle = 0.0_deg;

  const units::second_t LOOPTIME = 0.020_s;
  double m_deadZone = 24.0;
  double m_preLin = 0.0;
  double m_slowAngle = 45.0;

  double m_preError = 0.0;
  double m_sumError = 0.0;
  double m_kP = .0311;
  double m_kD = 0.004;
  double m_kI = 0.00;

  double m_kP_rot;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // variables used for detection software stuff
  const double MINIMUMDISTANCE = 5.0;
  bool m_hasAntiCollision = false;
  double m_lidarCollisionDistance = 70.0;
  double m_distanceCollisionDistanceLeft;
  double m_distanceCollisionDistanceRight;
};
