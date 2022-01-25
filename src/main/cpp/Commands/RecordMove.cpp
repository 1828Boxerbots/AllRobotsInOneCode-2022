// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/RecordMove.h"

RecordMove::RecordMove(const RecordMove& orig) 
{
  m_isFinished = orig.m_isFinished;
  m_pDrive = orig.m_pDrive;
  m_pController = orig.m_pController;

  m_plogfile = orig.m_plogfile;
  m_precordfile = orig.m_precordfile;
}

RecordMove::RecordMove(DriveTrainSubsystemBase *pDrive, frc::XboxController *pController)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pController = pController;

  m_pDrive = pDrive;
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void RecordMove::Initialize()
{
  m_frameCount = 0;
  m_plogfile = new std::ofstream;

  m_plogfile->open(LOG_FILE);

  m_timeStart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

  char filename[2560];
  std::string time = Util::TimeStampStr();
  Util::Log("Recode Time", time);
  sprintf(filename, "/u/c418_recording/recording_%s.bin", time.c_str());
  Util::Log("Record File Name", filename);
  m_precordfile = new std::ofstream;
  m_precordfile->open(filename, std::ios::out | std::ios::app | std::ios::binary);

  if(m_plogfile->is_open())
  {
    *m_plogfile << "Recording File = " << filename << "\n";
  }
}

// Called repeatedly when this Command is scheduled to run
void RecordMove::Execute()
{
 m_timeEnd = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

  double left = -m_pController->GetLeftY();
  double right = m_pController->GetRightX();
  right *= 0.75;
  
  if(left > -m_deadZone && left < m_deadZone)
  {
    left = 0;
  }
  if(right > -m_deadZone && right < m_deadZone)
  {
    right = 0;
  }

  m_pDrive->MoveArcade(left, right);

  //*m_plogfile << Util::TimeStampStr() << " Left = " << left << " Right = " << right << std::endl;

  RecordingStructure record;
  record.m_left = left;
  record.m_right = right;
  record.m_frameNum = m_frameCount++;
  strcpy(&record.m_time[0], Util::TimeStampStr().c_str());;
  record.m_sec = m_timeEnd - m_timeStart;
  record.m_gyro = m_pDrive->IMUGetAngle();

  m_timeCur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  if(m_precordfile->is_open())
  {
    m_precordfile->write( (char*)&record, sizeof(RecordingStructure) );
  }

  m_timeStart = m_timeCur;
}

// Called once the command ends or is interrupted.
void RecordMove::End(bool interrupted) {}

// Returns true when the command should end.
bool RecordMove::IsFinished() {
  return false;
}
