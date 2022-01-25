// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/PlayMove.h"

PlayMove::PlayMove(DriveTrainSubsystemBase *pDrive, const char *pfilename) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_filename = pfilename;

  m_pDrive = pDrive;
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void PlayMove::Initialize() 
{
  m_logfile.open(LOG_FILE);
  if(m_logfile.is_open())
  {
    m_logfile << "Looking File = " << m_filename << "\n";
  }

  m_inputFile.open(m_filename, std::ios::in | std::ios::binary);

  //Get length of the recorded file
  m_inputFile.seekg(0, std::ios::end);
  m_filelength = m_inputFile.tellg();

  m_logfile << "File: " << m_filename << " Length of file: " << m_filelength << std::endl;

  //Go back to beginning we are at the end of the file
  m_inputFile.seekg(0, std::ios::beg);

  //Allocate memory
  m_pbuffer = new char[m_filelength];

  //Read data in a block
  m_inputFile.read(m_pbuffer, m_filelength);
  m_inputFile.close();

  //Grab first byte
  m_pPlaybackPtr = &m_pbuffer[0];
}

// Called repeatedly when this Command is scheduled to run
void PlayMove::Execute()
{
  Util::Log("PlayMove Shadow1", "Exe Start");
  Util::Log("PlayMove Shadow2", beat++);
  //If accidently went here when finished return
  if(m_isFinished)
  {
    return;
  }

  // //Set Time
  // char currentTime[256];
  // std::string timeChar = Util::TimeStampStr();
  // sprintf(currentTime, "Time: %s", timeChar);
  // //Post time on log file
  // m_logfile << currentTime << std::endl;
  // //Log pointer position and size
  // m_logfile << "PlayBack = " << (long)m_pPlaybackPtr << " sizeof(RecordingStructure) = " << sizeof(RecordingStructure)
  //   << " Last Position = " << (long)(m_pbuffer + m_filelength) << std::endl;

  //Create left right variables
  double left = 0.0;
  double right = 0.0;
  double currentAngle = 0;

  int beat2 = 0;

  //While there is still file left contiue to read
  while((long)(m_pPlaybackPtr + sizeof(RecordingStructure)) < (long)(m_pbuffer + m_filelength))
  {
    Util::Log("PlayMove Shadow3", beat2++);
    Util::Log("PlayMove Shadow2", beat);

    //Set binary vaules to structure values
    RecordingStructure *pValues = (RecordingStructure *)m_pPlaybackPtr;

    //Verfiy sync
    if(pValues->m_sync1 == RecordingStructure::SYNC1 && pValues->m_sync2 == RecordingStructure::SYNC2)
    {
      //Set structure values to motor values
      left = pValues->m_left;
      right = pValues->m_right;
      
      //Log motor values in log file
      //m_logfile << "Left: " << left << " right: " << right << std::endl;

      currentAngle = m_pDrive->IMUGetAngle();
      Util::Log("PlayMove m_gyro", pValues->m_gyro);
      if(((currentAngle-5) < pValues->m_gyro || (currentAngle+5) > pValues->m_gyro) && beat > 0)
      {
        Util::Log("PlayMove Shadow1", "ROTATE");
        RotateToDegrees(pValues->m_gyro, 0.2);
        //m_pDrive->ForwardInInchGyro(1, 0.3);
      }

      //Move with Arcade
      m_pDrive->MoveArcade(left, right);

      //Get next data point
      m_pPlaybackPtr = (char*)(m_pPlaybackPtr + sizeof(RecordingStructure));

      Util::DelayInSeconds((units::second_t)pValues->m_sec / 1000.0);
    }
    else
    {
      //Move down one byte if sync is not alligned
      m_pPlaybackPtr = (char*)(m_pPlaybackPtr + 1);
      //m_logfile << "Sync off! NEXT!! " << std::endl;
    }
  }

  m_pDrive->Stop();
  m_isFinished = true;

  Util::Log("PlayMove Shadow1", "Exe End");
}

void PlayMove::RotateToDegrees(double degree, double speed)
{
  double currentAngle = m_pDrive->IMUGetAngle();
  
  double lowerDegree = degree - 5;
  double upperDegree = degree + 5;

  while(currentAngle > upperDegree || currentAngle < lowerDegree)
  {
    if(currentAngle > upperDegree)
    {
      m_pDrive->TurnRight(speed);
    }
    else if(currentAngle < lowerDegree)
    {
      m_pDrive->TurnLeft(speed);
    }
    currentAngle = m_pDrive->IMUGetAngle();
  }

  m_pDrive->Stop();
}

// Called once the command ends or is interrupted.
void PlayMove::End(bool interrupted) {}

// Returns true when the command should end.
bool PlayMove::IsFinished() 
{
  return m_isFinished;
}
