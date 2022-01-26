/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/C418/DriveTrainSubsystemC418.h"

DriveTrainSubsystemC418::DriveTrainSubsystemC418(I2CMultiplexerDriver *pMultiplexerDriver)
{
  #ifndef NOHW
  m_pMultiplexerDriver = pMultiplexerDriver;

#ifdef M_LIDAR
  m_pLidar = new MuxLidarDriver(I2C_PORT_MULTIPLEXER_C418, I2C_ADDR_LIDAR_C418, *m_pMultiplexerDriver, U8T_LINE_LIDAR_C418);
#endif

#ifdef M_DISTANCE_LEFT
  m_pMuxLeftDistance = new MuxDistanceSensorDriver(DISTANCESENSOR_PORT_C418, I2C_ADDR_LEFTDISTANCESENSOR_C418, *m_pMultiplexerDriver, U8T_LINE_LEFTDISTANCESENSOR_C418);
#endif

#ifdef M_DISTANCE_RIGHT
  m_pMuxRightDistance = new MuxDistanceSensorDriver(DISTANCESENSOR_PORT_C418, I2C_ADDR_RIGHTDISTANCESENSOR_C418, *m_pMultiplexerDriver, U8T_LINE_RIGHTDISTANCESENSOR_C418);
#endif

#endif
}

void DriveTrainSubsystemC418::SetMotorL(double speed)
{
#ifndef NOHW
  m_leftMotor.Set(speed * m_motorSpeed);
#endif

  //m_camera.Tick();
}

void DriveTrainSubsystemC418::SetMotorR(double speed)
{
#ifndef NOHW
  m_rightMotor.Set(speed * m_motorSpeed);
#endif

}

double DriveTrainSubsystemC418::GetMotorL()
{
#ifndef NOHW
  return m_leftMotor.Get();
#else
  return 0;
#endif

  //m_camera.Tick();
}

double DriveTrainSubsystemC418::GetMotorR()
{
#ifndef NOHW
  return m_rightMotor.Get();
#else
  return 0;
#endif

}

double DriveTrainSubsystemC418::WhereToTurn( double deadZoneLocation, int deadZoneRange)
{
  #ifndef NOHW
    return m_camera.WhereToTurn(deadZoneLocation, deadZoneRange);
  #else
    return 0.0;
  #endif

}

void DriveTrainSubsystemC418::Init()
{
  Util::Log("Camera Init", false);
#ifndef NOHW

  m_leftMotor.SetInverted(false);
  m_rightMotor.SetInverted(true);

  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
  m_leftEncoder.SetReverseDirection(true);
  m_rightEncoder.SetReverseDirection(true);
  m_leftEncoder.SetDistancePerPulse((1.0 / GetPulsesPerRevolution()) * Util::PI * WHEELDIAMETER);
  m_rightEncoder.SetDistancePerPulse((1.0 / GetPulsesPerRevolution()) * Util::PI * WHEELDIAMETER);
  m_camera.Init();
  Util::Log("Camera Init", true);

  #ifdef M_DISTANCE_RIGHT
    m_pMuxRightDistance->Init(true);
  #endif

  #ifdef M_DISTANCE_LEFT
    m_pMuxLeftDistance->Init(true);
  #endif
  #ifdef M_IMU
    m_imu.IMUGyroInit(true);
  #endif
#endif
}

void DriveTrainSubsystemC418::InitRight()
{
#ifdef M_DISTANCE_RIGHT
  m_pMuxRightDistance->Init(true);
#endif
}

void DriveTrainSubsystemC418::InitLeft()
{
#ifdef M_DISTANCE_LEFT
  m_pMuxLeftDistance->Init(true);
#endif
}

// Function for getting the current angle of the robot relative to its starting position
double DriveTrainSubsystemC418::IMUGetAngle()
{
  Util::Log("IsIMU", false);
  units::degree_t imuY = -1_deg;
  units::degree_t imuZ = -1_deg;
#ifndef NOHW
// If this isn't giving you the correct angle, try .GetAngleZ() or .GetAngleX()
#ifdef M_IMU
  m_imuAngle = m_imu.GetAngleX();
  imuY = m_imu.GetAngleY();
  imuZ = m_imu.GetAngleZ();
  // Util::Log("IMU X", m_imuAngle, "DriveTrainSubsystemC418");
  // Util::Log("IMU Z", imuZ, "DriveTrainSubsystemC418");
  // Util::Log("IMU Y", imuY, "DriveTrainSubsystemC418");

  // Util::Log("IMU correct X", m_imu.GetCorrectAngleX(), "DriveTrainSubsystemC418");
  // Util::Log("IMU correct Y", m_imu.GetCorrectAngleY(), "DriveTrainSubsystemC418");
  // Util::Log("IMU correct Z", m_imu.GetCorrectAngleZ(), "DriveTrainSubsystemC418");

  // Util::Log("IMU GetAngle", m_imu.GetAngle(), "DriveTrainSubsystemC418");
  
  Util::Log("IsIMU", true);
  return (double)m_imuAngle;
#else
  return 0;
#endif
#else
  return 0;
#endif
}

double DriveTrainSubsystemC418::GetLeftEncoderInch()
{
  m_leftEncoderSim++;
#ifndef NOHW
  m_leftEncoderSim = m_leftEncoder.GetDistance();
  Util::Log("LeftEncoder Distance", m_leftEncoderSim, "DriveTrainSubsystemC418");
  Util::Log("LeftEncoder Raw", m_leftEncoder.Get(), "DriveTrainSubsystemC418");
  Util::Log("LeftEncoder Direction", m_leftEncoder.GetDirection(), "DriveTrainSubsystemC418");
  Util::Log("LeftEncoder Running", m_leftEncoder.GetStopped(), "DriveTrainSubsystemC418");
#endif
  LogEncoder();
  return m_leftEncoderSim;
}

double DriveTrainSubsystemC418::GetRightEncoderInch()
{
  m_rightEncoderSim+=1.0;
#ifndef NOHW
  m_rightEncoderSim = m_rightEncoder.GetDistance();
  Util::Log("RightEncoder Distance", m_rightEncoderSim, "DriveTrainSubsystemC418");
  Util::Log("RightEncoder Raw", m_rightEncoder.Get(), "DriveTrainSubsystemC418");
  Util::Log("RightEncoder Direction", m_rightEncoder.GetDirection(), "DriveTrainSubsystemC418");
  Util::Log("RightEncoder Running", m_rightEncoder.GetStopped(), "DriveTrainSubsystemC418");
#endif
  LogEncoder();
  return m_rightEncoderSim;
}

double DriveTrainSubsystemC418::GetLeftEncoderRaw()
{
#ifndef NOHW
  Util::Log("LeftEncoder Raw", m_leftEncoder.Get(), "DriveTrainSubsystemC418");
  return m_leftEncoder.Get();
#else
  return -1;
#endif
}

double DriveTrainSubsystemC418::GetRightEncoderRaw()
{
#ifndef NOHW
  Util::Log("RightEncoder Raw", m_rightEncoder.Get(), "DriveTrainSubsystemC418");
  return m_rightEncoder.Get();
#else
  return -1;
#endif
}

void DriveTrainSubsystemC418::ResetEncoder()
{
#ifndef NOHW
  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
#endif
  m_rightEncoderSim = 0.0;
  m_leftEncoderSim = 0.0;
  LogEncoder();
}

// Currently using IMU
units::degree_t DriveTrainSubsystemC418::GyroGetAngle()
{
#ifdef M_IMU
  units::degree_t m_gyroAngle = -1_deg;
  #ifndef NOHW
  m_gyroAngle = m_imu.GetAngleX();
  #endif
  //m_imu.LogAllValues(); //causes lag
  return m_gyroAngle;
#else
  return 0;
#endif
}

double DriveTrainSubsystemC418::GetDistanceSensorDetectionDistanceLeft()
{
  //------------------------------------
  double val = -1;
#ifndef NOHW
#ifdef M_DISTANCE_LEFT

  /*if(m_hasAntiCollision == false)
  {
    return 1;
  }*/
  m_pMuxLeftDistance->Init(true);
  val = m_pMuxLeftDistance->GetDistance();
#endif
  Util::Log("DriveTrain Distance Left", val);
  //Util::DelayInSeconds(1);
#endif
  return val;
}

double DriveTrainSubsystemC418::GetDistanceSensorDetectionDistanceRight()
{
  //-------------------------------------
  double val = -1;
#ifndef NOHW
#ifdef M_DISTANCE_RIGHT

  /*if(m_hasAntiCollision == false)
  {
    return 1;
  }*/
  m_pMuxRightDistance->Init(true);
  val = m_pMuxRightDistance->GetDistance();
#endif
  Util::Log("DriveTrain Distance Right", val);
  //Util::DelayInSeconds(1);
#endif
  return val;
}

double DriveTrainSubsystemC418::GetLidarDetectionDistance()
{
#ifndef NOHW
#ifdef M_LIDAR
  /*if(m_hasAntiCollision == false)
  {
    return 1;
  }*/
  double val = m_pLidar->GetDistanceInInches();
  frc::SmartDashboard::PutNumber("DriveTrain Lidar", val);
  return val;
#else
  return 1;
#endif
#else
  return 1;
#endif
}

//Makes is so that the robot doesn't run into things head on
/*
//Don't really know what this code is doing, but considering that stop is commented out, it might be the first iteration of detection software. Meat of code found in Drive base cpp
void DriveTrainSubsystemC418::DetectionSoftware(double detectionDistance)
{
  #ifndef NOHW
  frc::SmartDashboard::PutNumber("Lidar Distance", GetLidarDetectionDistance());
  double currentDetection = GetLidarDetectionDistance();
  frc::SmartDashboard::PutBoolean("DistanceDetection", false);
  frc::SmartDashboard::PutBoolean("DistanceSensor DistanceDetection", false);
    if(currentDetection < detectionDistance)
    {
        frc::SmartDashboard::PutBoolean("DistanceDetection", true);
        //Stop();
    }
    currentDetection = GetLidarDetectionDistance();
    if(currentDetection < detectionDistance)
    {
      frc::SmartDashboard::PutBoolean("DistanceSensor DistanceDetection", true);
    }
    
    #endif
}
*/

//Sets up dead zone in lidar
void DriveTrainSubsystemC418::PrecisionMovementLidar(double wantedDistance, double speed)
{
#ifdef M_LIDAR
  const double DEAD_ZONE = 5.0;
  double currentDistance =  -1;
  #ifndef NOHW
  currentDistance = m_pLidar->GetDistanceInInches();
  #endif
  Util::Log("Lidar", "Activated");
  if(currentDistance < 0) {  Util::Log("Lidar","No See");  }
  while (currentDistance < (wantedDistance - DEAD_ZONE) || currentDistance > (wantedDistance + DEAD_ZONE))
  {
    if (currentDistance < wantedDistance - DEAD_ZONE)
    {
      Forward(-speed);
    }
    if (currentDistance > wantedDistance + DEAD_ZONE)
    {
      Forward(speed);
    }
    #ifndef NOHW
    currentDistance = m_pLidar->GetDistanceInInches();
    #endif
    Util::Log("LidarDistance", currentDistance);
  }
  Stop();
#endif
}

void DriveTrainSubsystemC418::GoAroundCone(bool turnRight)
{
  frc::Timer timer;

  if (turnRight == false)
  { 
    units::second_t seconds = 3.5_s;
    units::second_t startTime = timer.Get();
    units::second_t currentTime = timer.Get();
    //Keep looping until end time is reached
    timer.Start();
    while (currentTime - startTime < seconds)
    {
        //Gets current time and sends it to the smartdashboard for checking
        currentTime = timer.Get();
        MoveArcade(0.6,-0.2);
    }
    timer.Stop();
    timer.Reset();
  }
  else if(turnRight == true)
  {
    units::second_t seconds = 3.5_s;
    units::second_t startTime = timer.Get();
    units::second_t currentTime = timer.Get();
    //Keep looping until end time is reached
    timer.Start();
    while (currentTime - startTime < seconds)
    {
        //Gets current time 
        currentTime = timer.Get();
        MoveArcade(0.5, 0.2);
    }
    timer.Stop();
    timer.Reset();
  }

//   IMUInit();
//   while(IMUGetAngle() < -361)
// {
//   Util::Log("Shadow 2","while IMU-1");
//   double rightDistance = GetDistanceSensorDetectionDistanceRight();
//   if (rightDistance < 0.0)
//   {
//     TurnRight(0.3);
//   }
//   else
//   {
//     Forward(0.3);
//   }
//   Util::Log("Shadow 2","while IMU-2");
// }
// Stop();
}

// void DriveTrainSubsystemC418::MoveArcade(double X, double Y)
// {
//   m_difDrive.ArcadeDrive(X,Y);
// }

void DriveTrainSubsystemC418::SetHSVHigh(int HSV, int value)
{
  #ifndef NOHW
    m_camera.SetHigh(HSV, value);
  #endif
}

void DriveTrainSubsystemC418::SetHSVLow(int HSV, int value)
{
  #ifndef NOHW
    m_camera.SetLow(HSV, value);
  #endif
}

void DriveTrainSubsystemC418::SetVisionFMSColor(OldCameraVision::VisionColors color)
{
  #ifndef NOHW
    m_camera.SetFMSColor(color);
  #endif
}

void DriveTrainSubsystemC418::SetLookingColorV(OldCameraVision::VisionColors color)
{
  #ifndef NOHW
    m_camera.SetLookingColor(color);
  #endif
}

OldCameraVision::VisionColors DriveTrainSubsystemC418::GetLookingColorV()
{
  #ifndef NOHW
    return m_camera.GetLookingColor();
  #else
    return OldCameraVision::VisionColors::INVALID_COLOR;
  #endif
}

double DriveTrainSubsystemC418::GetCentroidY()
{
  #ifndef NOHW
  return m_camera.GetCentroidY();
  #endif
}

double DriveTrainSubsystemC418::GetCentroidX()
{
  #ifndef NOHW
  return m_camera.GetCentroidX();
  #endif
}

void DriveTrainSubsystemC418::SetVisionCrop(int cropX, int cropY, int cropW, int cropH)
{
  #ifndef NOHW
  m_camera.SetCrop(cropX, cropY, cropW, cropH);
  #endif
}

void DriveTrainSubsystemC418::GetVisionSize(int *pHeight, int *pWidth)
{
  #ifndef NOHW
  m_camera.GetSize(pHeight, pWidth);
  #endif
}

void DriveTrainSubsystemC418::SetContArea(bool isLow, double value)
{
  #ifndef NOHW
    if(isLow)
    {
      m_camera.m_minArea = value;
    }
    else
    {
      m_camera.m_maxArea = value;
    }
  #endif
}
void DriveTrainSubsystemC418::SetContRatio(bool isLow, double value)
{
  #ifndef NOHW
    if(isLow)
    {
      m_camera.m_minRatio = value;
    }
    else
    {
      m_camera.m_maxRatio = value;
    }
  #endif
}
void DriveTrainSubsystemC418::SetContSolid(bool isLow, double value)
{
  #ifndef NOHW
    if(isLow)
    {
      m_camera.m_minSolid = value;
    }
    else
    {
      m_camera.m_maxSolid = value;
    }
  #endif
}

void DriveTrainSubsystemC418::SetContSave()
{
  #ifndef NOHW
    //Area, Ratio, Solid
    //Low, high
    m_camera.m_minSolid = m_camera.m_saveCheck[0];
    m_camera.m_maxSolid = m_camera.m_saveCheck[1];
    m_camera.m_minRatio = m_camera.m_saveCheck[2];
    m_camera.m_maxRatio = m_camera.m_saveCheck[3];
    m_camera.m_minSolid = m_camera.m_saveCheck[4];
    m_camera.m_maxSolid = m_camera.m_saveCheck[5];
  #endif
}

//Used to disable and enable anticollision
void DriveTrainSubsystemC418::EnableAnticollision(bool enable)
{
  Util::Log("EAB", m_beat++, "DriveTrain2020");
  Util::Log("enabled?", enable, "DriveTrain2020");
  m_hasAntiCollision = enable;
  /*
  if(enable == true)
  {
    #ifdef M_DISTANCE
    m_pMuxLeftDistance->Init(true);
    m_pMuxRightDistance->Init(true);
    #endif
  }
  else 
  {
    #ifdef M_DISTANCE
    m_pMuxLeftDistance->Init(false);
    m_pMuxRightDistance->Init(false);
    #endif
  }*/
}

/*
Detection code ripped from Rocky code for Robot 2020
//Gets Detection distance; used for debugging
double DriveTrainSubsystemRocky::GetLidarDetectionDistance()
{
  double val = m_pLidar->GetDistanceInInches();
   frc::SmartDashboard::PutNumber("DriveTrain Lidar", val);
  return val;
}


//Makes is so that the robot doesn't run into things head on
void DriveTrainSubsystemRocky::DetectionSoftware(double detectionDistance)
{
    frc::SmartDashboard::PutNumber("Lidar Distance", GetLidarDetectionDistance());
    double currentDetection = GetLidarDetectionDistance();
    frc::SmartDashboard::PutBoolean("DistanceDetection", false);
        if(currentDetection < detectionDistance)
        {
            frc::SmartDashboard::PutBoolean("DistanceDetection", true);
            //Stop();
        }
}


//Sets up dead zone in lidar
void DriveTrainSubsystemRocky::PrecisionMovementLidar(double wantedDistance)
{
  const double DEAD_ZONE = 5.0;
  double currentDistance = m_pLidar->GetDistanceInInches();
  while(wantedDistance <  currentDistance + DEAD_ZONE && wantedDistance > currentDistance - DEAD_ZONE)
  {
    if(currentDistance < wantedDistance)
    {
      MoveTank(-.5,-.5);
    }
    if(currentDistance > wantedDistance)
    {
      MoveTank(.5,.5);
    }
    currentDistance = m_pLidar->GetDistanceInInches();
  }
}
*/
