/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Rocky/DriveTrainSubsystemRocky.h"
#include <frc/smartdashboard/SmartDashboard.h>

DriveTrainSubsystemRocky::DriveTrainSubsystemRocky() {}

void DriveTrainSubsystemRocky::SetMotorL(double speed)
{
#ifndef NOHW
  m_leftMotor.Set(speed * m_scale);
#endif
  frc::SmartDashboard::PutNumber("Drive Left", speed);
}

void DriveTrainSubsystemRocky::SetMotorR(double speed)
{
#ifndef NOHW
  m_rightMotor.Set(speed * m_scale);
#endif
  frc::SmartDashboard::PutNumber("Drive Right", speed);
}

//function made for debugging with gyro and easy changes
units::degree_t DriveTrainSubsystemRocky::GyroGetAngle()
{
#ifndef NOHW
  m_gyroAngle = m_gyro.GetAngle();
  //frc::SmartDashboard::PutNumber("GyroAngle", m_gyroAngle);
  return m_gyroAngle;
#else
  return 0_deg;
#endif
}

//Initializes gyro, Run only once
void DriveTrainSubsystemRocky::GyroInit()
{
#ifndef NOHW
  bool gyroIsIntiliazed = false;
  if (gyroIsIntiliazed == false)
  {
    frc::SmartDashboard::PutBoolean("GyroInit", true);
    m_gyro.Reset();
    m_gyro.Calibrate();
    gyroIsIntiliazed = true;
  }
#endif
}

double DriveTrainSubsystemRocky::GetLeftEncoderInch()
{
  m_leftEncoderSim++;
#ifndef NOHW
  m_leftEncoderSim = m_leftEncoder.GetDistance();
  frc::SmartDashboard::PutNumber("LeftEncoder Raw", m_leftEncoder.Get());
  frc::SmartDashboard::PutBoolean("LeftEncoder Direction", m_leftEncoder.GetDirection());
  frc::SmartDashboard::PutBoolean("LeftEncoder Running", m_leftEncoder.GetStopped());
#endif
  LogEncoder();
  return m_leftEncoderSim;
}

double DriveTrainSubsystemRocky::GetRightEncoderInch()
{
  m_rightEncoderSim++;
#ifndef NOHW
  m_rightEncoderSim = m_rightEncoder.GetDistance();
  frc::SmartDashboard::PutNumber("RightEncoder Raw", m_rightEncoder.Get());
  frc::SmartDashboard::PutBoolean("RightEncoder Direction", m_rightEncoder.GetDirection());
  frc::SmartDashboard::PutBoolean("RightEncoder Running", m_rightEncoder.GetStopped());
#endif
  LogEncoder();
  return m_rightEncoderSim;
}

//Initializes motor encoders and drive motors
void DriveTrainSubsystemRocky::Init()
{
#ifndef NOHW
  m_leftMotor.SetInverted(false);
  m_rightMotor.SetInverted(true);
  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
  m_leftEncoder.SetReverseDirection(true);
  m_rightEncoder.SetReverseDirection(true);
  //m_leftEncoder.SetDistancePerPulse((WHEELDIAMETER*Util::PI)/PULSE_PER_REVOLUTION);
  //m_rightEncoder.SetDistancePerPulse((WHEELDIAMETER*Util::PI)/PULSE_PER_REVOLUTION);
  m_leftEncoder.SetDistancePerPulse((1.0 / GetPulsesPerRevolution()) * Util::PI * WHEELDIAMETER);
  m_rightEncoder.SetDistancePerPulse((1.0 / GetPulsesPerRevolution()) * Util::PI * WHEELDIAMETER);

  m_camera.Init();
#endif
}

//Resets Encoders and logs them
void DriveTrainSubsystemRocky::ResetEncoder()
{
#ifndef NOHW
  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
#endif

  m_rightEncoderSim = 0.0;
  m_leftEncoderSim = 0.0;
  LogEncoder();
}

void DriveTrainSubsystemRocky::Periodic() {}

//Gets Detection distance; used for debugging
double DriveTrainSubsystemRocky::GetLidarDetectionDistance()
{
#ifndef NOHW
  double val = m_lidar.GetDistanceInInches();
  frc::SmartDashboard::PutNumber("DriveTrain Lidar", val);
  return val;
#else
  return 0;
#endif
}

//Makes is so that the robot doesn't run into things head on
/*
void DriveTrainSubsystemRocky::DetectionSoftware(double detectionDistance)
{
  #ifndef NOHW
    frc::SmartDashboard::PutNumber("Lidar Distance", GetLidarDetectionDistance());
    double currentDetection = GetLidarDetectionDistance();
    frc::SmartDashboard::PutBoolean("DistanceDetection", false);
        if(currentDetection < detectionDistance)
        {
            frc::SmartDashboard::PutBoolean("DistanceDetection", true);
            //Stop();
        }
  #endif
}
*/

//Sets up dead zone in lidar
void DriveTrainSubsystemRocky::PrecisionMovementLidar(double wantedDistance, double speed)
{
#ifndef NOHW
  const double DEAD_ZONE = 5.0;
  double currentDistance = m_lidar.GetDistanceInInches();
  //Logic that moves the robot back or forth to the prefered distance for auto
  while (wantedDistance < (currentDistance + DEAD_ZONE) && wantedDistance > (currentDistance - DEAD_ZONE))
  {
    if (currentDistance < wantedDistance)
    {
      MoveTank(-.5, -.5);
    }
    if (currentDistance > wantedDistance)
    {
      MoveTank(.5, .5);
    }
    currentDistance = m_lidar.GetDistanceInInches();
  }
#endif
}

void DriveTrainSubsystemRocky::EnableAnticollision(bool enable)
{
  enable = false;
  m_hasAntiCollision = enable;
}


double DriveTrainSubsystemRocky::WhereToTurn( double deadZoneLocation, int deadZoneRange)
{
  #ifndef NOHW
    return m_camera.WhereToTurn(deadZoneLocation, deadZoneRange);
  #endif
}

void DriveTrainSubsystemRocky::SetHSVHigh(int HSV, int value)
{
  #ifndef NOHW
    m_camera.SetHigh(HSV, value);
  #endif
}

void DriveTrainSubsystemRocky::SetHSVLow(int HSV, int value)
{
  #ifndef NOHW
    m_camera.SetLow(HSV, value);
  #endif
}

void DriveTrainSubsystemRocky::SetVisionFMSColor(OldCameraVision::VisionColors color)
{
  #ifndef NOHW
    m_camera.SetFMSColor(color);
  #endif
}

void DriveTrainSubsystemRocky::SetLookingColorV(OldCameraVision::VisionColors color)
{
  #ifndef NOHW
    m_camera.SetLookingColor(color);
  #endif
}

OldCameraVision::VisionColors DriveTrainSubsystemRocky::GetLookingColorV()
{
  #ifndef NOHW
    return m_camera.GetLookingColor();
  #else
    return OldCameraVision::VisionColors::INVALID_COLOR;
  #endif
}

double DriveTrainSubsystemRocky::GetCentroidY()
{
  #ifndef NOHW
  return m_camera.GetCentroidY();
  #endif
}

double DriveTrainSubsystemRocky::GetCentroidX()
{
  #ifndef NOHW
  return m_camera.GetCentroidX();
  #endif
}

void DriveTrainSubsystemRocky::SetVisionCrop(int cropX, int cropY, int cropW, int cropH)
{
  #ifndef NOHW
  m_camera.SetCrop(cropX, cropY, cropW, cropH);
  #endif
}

void DriveTrainSubsystemRocky::GetVisionSize(int *pHeight, int *pWidth)
{
  #ifndef NOHW
  m_camera.GetSize(pHeight, pWidth);
  #endif
}