/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/motorcontrol/Spark.h>
#include <frc/Encoder.h>
#include "../DriveTrainSubsystemBase.h"
#include "../../Drivers/AM3313HallEffectDriver.h"
#include "../../Drivers/LidarDriver.h"
#include "../../Drivers/ADXRS_450GyroDriver.h"
#include <frc/ADIS16448_IMU.h>
#include "../../Drivers/CameraDrivers/OldCameraVision.h"

class DriveTrainSubsystemRocky : public DriveTrainSubsystemBase
{
public:
  DriveTrainSubsystemRocky();

  void SetMotorL(double speed) override;
  void SetMotorR(double speed) override;
  units::degree_t GyroGetAngle() override;
  void GyroInit() override;
  void Init() override;
  double GetLeftEncoderInch() override;
  double GetRightEncoderInch() override;
  void ResetEncoder() override;
  void Periodic() override;
  //void DetectionSoftware(double detectionDistance) override;
  double GetLidarDetectionDistance() override;
  void PrecisionMovementLidar(double wantedDistance, double speed = 0.5) override;
  double GetPulsesPerRevolution() override { return PULSE_PER_REVOLUTION; }
  void EnableAnticollision(bool enable) override;

  double WhereToTurn( double deadZoneLocation = 0.0, int deadZoneRange = 100) override;
  void SetHSVHigh(int HSV, int value) override;
  void SetHSVLow(int HSV, int value) override;
  void SetLookingColorV(OldCameraVision::VisionColors) override;
  double GetCentroidY() override;
  double GetCentroidX() override;
  OldCameraVision::VisionColors GetLookingColorV() override;
  void SetVisionCrop(int cropX = 0, int cropY = 0, int cropW = 240, int cropH = 320) override;
  void GetVisionSize(int *pHeight, int *pWidth) override;
  void SetVisionFMSColor(OldCameraVision::VisionColors color);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

private:
#ifndef NOHW
  frc::Spark m_leftMotor{PWM_LEFTMOTOR_ROCKY};
  frc::Spark m_rightMotor{PWM_RIGHTMOTOR_ROCKY};
  frc::Encoder m_leftEncoder{DIO_LEFTENCODER_ROCKY_ONE, DIO_LEFTENCODER_ROCKY_TWO};
  frc::Encoder m_rightEncoder{DIO_RIGHTENCODER_ROCKY_ONE, DIO_RIGHTENCODER_ROCKY_TWO};
  frc::ADIS16448_IMU m_gyro;
  LidarDriver m_lidar{frc::I2C::Port::kOnboard, LidarDriver::LIDAR_ADDRESS};

  OldCameraVision m_camera{0};
#endif

  const double PULSE_PER_REVOLUTION = 240;
  const double WHEELDIAMETER = 8.0;
  double m_scale = 0.7;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
