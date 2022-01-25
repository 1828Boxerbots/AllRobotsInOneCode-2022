// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <iostream>
#include <fstream>

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveTrainSubsystemBase.h"
#include "RecordingStructure.h"


/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class PlayMove
    : public frc2::CommandHelper<frc2::CommandBase, PlayMove> {
 public:
  PlayMove(DriveTrainSubsystemBase *pDrive, const char *pfilename);

  void Initialize() override;

  void Execute() override;

  void RotateToDegrees(double degree, double speed = 0.5);

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  bool m_isFinished = false;
  DriveTrainSubsystemBase *m_pDrive = nullptr;

  std::string m_filename;
  std::ifstream m_inputFile;
  long m_filelength = 0;
  char *m_pbuffer = nullptr;
  char *m_pPlaybackPtr = nullptr;

  time_t m_preClock = 0;
  int beat = 0;

  std::ofstream m_logfile;
  const std::string LOG_FILE = "/u/c418_recording/PlayMove_logfile.txt";
};
