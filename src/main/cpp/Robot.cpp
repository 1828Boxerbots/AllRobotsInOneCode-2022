/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

void Robot::VisionThread()
{
    // // Init()
    // cs::UsbCamera camera = frc::CameraServer::StartAutomaticCapture();
    // camera.SetResolution(640, 480);
    // cs::CvSink cvSink = frc::CameraServer::GetVideo();
    // cs::CvSource outputStreamStd = frc::CameraServer::PutVideo("Gray", 640, 480);
    // cv::Mat source;
    // cv::Mat output;

    // while(true) {
    //   // GrabFrame
    //   int  validImage = cvSink.GrabFrame(source);
    //   // Where To Turn
    //   if (validImage == 0) {
    //     continue;
    //   }

    //   // process imag
    //   cv::cvtColor(source, output, cv::COLOR_BGR2GRAY);
    //   outputStreamStd.PutFrame(output);
    // }

    // CameraVision cam{0};
    // cam.Init();
    // while (true)
    // {
    //   cam.Tick();
    // }
}

void Robot::RobotInit()
{
  // std::thread visionThread(VisionThread);
  // visionThread.detach();
  
  m_timer.Start();
  m_timer.Reset();
}



/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
  frc2::CommandScheduler::GetInstance().Run();
  //units::second_t time = m_timer.Get() - m_startTime;
  //Util::Log("TeleOp Timer", time);
  m_startTime = m_timer.Get();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit()
{
  m_container.Init();
  m_container.DisableInit();
}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit()
{
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand != nullptr)
  {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic()
{
  m_container.AutonomousPeriodic();
}

void Robot::TeleopInit()
{
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr)
  {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  m_container.TeleopPeriodic();
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
