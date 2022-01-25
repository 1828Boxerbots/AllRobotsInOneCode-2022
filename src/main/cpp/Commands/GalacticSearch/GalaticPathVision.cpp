// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include "subsystems/C418/LoaderSubsystemC418.h"
#include "Commands/GalacticSearch/GalaticPathVision.h"


GalaticPathVision::GalaticPathVision(DriveTrainSubsystemBase *pDrive, LoaderSubsystemBase *pLoader)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  m_pLoader = pLoader;

  AddRequirements(pLoader);
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void GalaticPathVision::Initialize()
{
  Util::Log("GV Shadow", "InitS");
  m_pDrive->SetLookingColorV(m_color);
  m_pDrive->GetVisionSize(&m_height, &m_width);
  
  m_startAngle = m_pDrive->IMUGetAngle();

  Util::Log("GV Shadow", "InitE");
}

// Called repeatedly when this Command is scheduled to run
void GalaticPathVision::Execute()
{
  m_pDrive->SetVisionCrop((m_width/2) - (rioW/2), (m_height*0.75) - 5, rioW, m_height*0.25);
  m_pDrive->WhereToTurn(0, m_deadZone);

  Util::Log("GV Shadow", "ExeS");
  if(m_isFinished == false)
  {
    switch(CheckRun())
    {
      case RED_ONE:
        Util::Log("GV Shadow", "ExeRed1");
        RunRedOne();
        break;
      case RED_TWO:
        Util::Log("GV Shadow", "ExeRed2");
        RunRedTwo();
        break;
      case BLUE_ONE:
        Util::Log("GV Shadow", "ExeBlue1");
        RunBlueOne();
        break;
      case BLUE_TWO:
        Util::Log("GV Shadow", "ExeBlue2");
        RunBlueTwo();
        break;
      default:
        Util::Log("GV Shadow", "DEFAULT-ERROR");
        m_isFinished = true;
        break;
    }
  }
}

int GalaticPathVision::CheckRun()
{
  Util::Log("GV Shadow", "CheckRunCrop");
  //Set Crop to Center
	m_pDrive->SetVisionCrop((m_width/2) - (rioW/2), (m_height*0.75)+10, rioW, m_height*0.25-10);
  // m_pDrive->WhereToTurn(0, m_deadZone);
  // Util::DelayInSeconds(1);
  //Can find Image return Red1
  Util::Log("GV Shadow", "CheckRun Where");
  if(m_pDrive->WhereToTurn(0, m_deadZone) > -2)
  {
    m_iteration = RED_ONE;
    return RED_ONE;
  }

  //Turn Left
  Util::Log("GV Shadow", "CheckRun Turn");
	//m_pDrive->TurnInDegrees(-10, m_moveSpeed/2);
  RotateToDegree(19.5);
  //Can Find Image Return Red2
  Util::Log("GV Shadow", "CheckRun Where");
  double result = m_pDrive->WhereToTurn(-1, m_deadZone);
  Util::DelayInSeconds(1.7_s);
  if(result > -2)
  {
    m_iteration = RED_TWO;
    return RED_TWO;
  }

  RotateToDegree(0);
  //Move 15 feet
  Util::Log("GV Shadow", "CheckRun Forward");
  m_pDrive->ForwardInInchGyro(120, m_moveSpeed);
  //Can find Image return Blue1 and if cant find image return Blue2
  Util::Log("GV Shadow", "CheckRun Where");
  return BLUE_TWO;
  
}

void GalaticPathVision::RunRedOne()
{

  //GetBallOne
  Util::Log("GV Shadow", "R1 Ball1");
  //FaceBall(false, 0.05);
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE_AND_BOTTOM);
  m_pDrive->ForwardInInchGyro(75, m_moveSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();
  //GetBallTwo
  Util::Log("GV Shadow", "R1 Ball2");
  RotateToDegree(-40);
  FaceBall(true, 0.05_s);
  m_pLoader->SetLoadMotor(m_loaderSpeed);
  m_pDrive->ForwardInInchGyro(55, m_moveSpeed);
  Util::DelayInSeconds(0.7_s);
  m_pLoader->Stop();
  //GetBallThree
  Util::Log("GV Shadow", "R1 Ball3");
  RotateToDegree(50, 0.2);
  m_pDrive->ForwardInInchGyro(6, m_moveSpeed/2);
  // bool turn = true;
  // if(m_pDrive->GyroGetAngle() > 50)
  // {
  //   turn = false;
  // }
  FaceBall(true, 0.04_s, 0.2);

  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE);
  m_pDrive->ForwardInInchGyro(73, m_moveSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();

  //ToEndZone
  Util::Log("GV Shadow", "R1 Endzone");
  RotateToEnd();
  m_pDrive->ForwardInInchGyro(130, m_moveSpeed);

  Util::Log("GV Shadow", "R1 Finished");
  m_isFinished = true;
}

void GalaticPathVision::RunRedTwo()
{
  //Get First Ball
  Util::Log("GV Shadow", "R2 Ball1");
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE_AND_BOTTOM);
  m_pDrive->ForwardInInchGyro(80, m_moveSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();
  //Get Second Ball
  Util::Log("GV Shadow", "R2 Ball2");
  RotateToDegree(-55); //Turn towards Ball
  Util::DelayInSeconds(0.5_s);
  FaceBall(true);
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE_AND_BOTTOM);
  m_pDrive->ForwardInInchGyro(80, m_moveSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();
  //Get Third Ball
  Util::Log("GV Shadow", "R2 Ball3");
  RotateToDegree(45); //Turn Towards ball
  Util::DelayInSeconds(0.3_s);
  FaceBall(true);
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE);
  m_pDrive->ForwardInInchGyro(90, m_moveSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();
  //Move towards end zone
  Util::Log("GV Shadow", "R2 EndZone");
  //m_pDrive->TurnInDegrees(90, m_moveSpeed);
  RotateToEnd();
  m_pDrive->ForwardInInchGyro(90, m_moveSpeed);
  
  Util::Log("GV Shadow", "R2 Finished");
  m_isFinished = true;
}

void GalaticPathVision::RunBlueOne()
{
  //Get ball one
  Util::Log("GV Shadow", "B1 Ball1");
  RotateToDegree(-30); //Turn toward ball
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE_AND_BOTTOM);
  m_pDrive->ForwardInInchGyro(67.2, m_moveSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();
  //Get Ball two
  Util::Log("GV Shadow", "B1 Ball2");
  RotateToDegree(80);  //Turn toward ball
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE_AND_BOTTOM);
  m_pDrive->ForwardInInchGyro(100, m_moveSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();
  //GetBall 3
  Util::Log("GV Shadow", "B1 Ball3");
  RotateToDegree(-35); //Turn toward ball and end
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE);
  m_pDrive->ForwardInInchGyro(50, m_moveSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();

  //Go to End
  Util::Log("GV Shadow", "B1 End");
  RotateToEnd();
  m_pDrive->ForwardInInchGyro(60, m_moveSpeed);

  Util::Log("GV Shadow", "B1 Finished");
  m_isFinished = true;
}

void GalaticPathVision::RunBlueTwo()
{
  //Get first ball
  Util::Log("GV Shadow", "B2 Ball1");
  RotateToDegree(-30);
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE_AND_BOTTOM);
  m_pDrive->ForwardInInchGyro(70, m_moveSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();

  //Get Second ball
  Util::Log("GV Shadow", "B2 Ball2");
  RotateToDegree(80);  //Turn toward ball
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE_AND_BOTTOM);
  m_pDrive->ForwardInInchGyro(84, m_moveSpeed);
  Util::DelayInSeconds(0.7_s);
  m_pLoader->Stop();

  //Get third ball and go to end zone
  Util::Log("GV Shadow", "B2 Ball1 3 & end");
  RotateToDegree(-40); //Turn toward ball and end
  FaceBall(true);
  m_pLoader->SetLoadMotor(m_loaderSpeed, LoaderSubsystemC418::MOTOR_INTAKE);
  m_pDrive->ForwardInInchGyro(96);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->Stop();

  Util::Log("GV Shadow", "B2 Finished");
  m_isFinished = true;
}

void GalaticPathVision::FaceBall(bool turnLeft, units::second_t delay, double speed)
{
  if(speed < -1)
  {
    speed = m_turnSpeed;
  }

  frc::Timer timer;
  timer.Reset();
  timer.Start();
  units::second_t startTime = timer.Get();
  units::second_t currentTime = timer.Get();

  double result = m_pDrive->WhereToTurn(0, m_deadZone);

  while(result != 0)
  {

    if(result > 0)
    {
      m_pDrive->TurnRight(m_moveSpeed/2);
      Util::DelayInSeconds(delay);
      m_pDrive->Stop();
    }
    else if(result < -2)
    {
      if(turnLeft)
      {
        m_pDrive->TurnLeft(m_moveSpeed/2);
        Util::DelayInSeconds(delay);
        m_pDrive->Stop();
      }
      else
      {
        m_pDrive->TurnRight(m_moveSpeed/2);
        Util::DelayInSeconds(delay);
        m_pDrive->Stop();
      }
    }
    else if(result < 0)
    {
      m_pDrive->TurnLeft(m_moveSpeed/2);
      Util::DelayInSeconds(delay);
      m_pDrive->Stop();
    }
    else if(result == 0)
    {
      break;
    }

    currentTime = timer.Get();
    //Util::Log("Galatic Timer", currentTime-startTime);
    if(currentTime-startTime >= 8_s)
    {
      turnLeft != turnLeft;
      startTime = currentTime;
    }

    result = m_pDrive->WhereToTurn(0, m_deadZone);
  }
}

void GalaticPathVision::RotateToEnd()
{
  double currentAngle = m_pDrive->IMUGetAngle();
  
  double lowerStart = m_startAngle - m_angleDed;
  double upperStart = m_startAngle + m_angleDed;

  while(currentAngle > upperStart || currentAngle < lowerStart)
  {
    if(currentAngle > upperStart)
    {
      m_pDrive->TurnRight(m_turnSpeed);
    }
    else if(currentAngle < lowerStart)
    {
      m_pDrive->TurnLeft(m_turnSpeed);
    }
    currentAngle = m_pDrive->IMUGetAngle();
  }

  m_pDrive->Stop();
}

void GalaticPathVision::RotateToDegree(double degree, double speed)
{
  if(speed < -1)
  {
    speed = m_turnSpeed;
  }

  double currentAngle = m_pDrive->IMUGetAngle();
  
  double lowerDegree = degree - 1;
  double upperDegree = degree + 2;

  while(currentAngle > upperDegree || currentAngle < lowerDegree)
  {
    if(currentAngle > upperDegree)
    {
      m_pDrive->TurnRight(speed);
    }
    else if(currentAngle < lowerDegree)
    {
      m_pDrive->TurnLeft(speed * 1.2);
    }
    currentAngle = m_pDrive->IMUGetAngle();
  }

  m_pDrive->Stop();
}

// Called once the command ends or is interrupted.
void GalaticPathVision::End(bool interrupted) {}

// Returns true when the command should end.
bool GalaticPathVision::IsFinished() 
{
  if(m_isFinished == true)
  {
    m_pDrive->Stop();
    m_pLoader->Stop();
  }
  return m_isFinished;
}
