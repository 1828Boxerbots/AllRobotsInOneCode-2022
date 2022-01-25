// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/XboxController.h>
#include "RecordingStructure.h"
#include "../subsystems/DriveTrainSubsystemBase.h"
#include "Util.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class RecordMove
    : public frc2::CommandHelper<frc2::CommandBase, RecordMove> {
 public:
  RecordMove(const RecordMove& orig);
  RecordMove(DriveTrainSubsystemBase *pDrive, frc::XboxController *pController);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    bool m_isFinished = false;
    double m_deadZone = 0.01;
    int m_frameCount = 0;

    long long m_timeStart;
    long long m_timeEnd;
    long long m_timeCur;

    DriveTrainSubsystemBase *m_pDrive;
    frc::XboxController *m_pController;

    std::ofstream *m_plogfile;
    std::ofstream *m_precordfile;

    const std::string LOG_FILE = "/u/c418_recording/RecordMove_logfile.txt";
};
