/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/RevDistanceDriver.h"

RevDistanceDriver::RevDistanceDriver(rev::Rev2mDistanceSensor::Port port, rev::Rev2mDistanceSensor::DistanceUnit unit, rev::Rev2mDistanceSensor::RangeProfile profile)
{
  m_pDistance = new rev::Rev2mDistanceSensor(port, unit, profile);
}

void RevDistanceDriver::Init(bool log)
{
  if (log)
  {
    Util::Log("Distance Sensor Initialized?", true, "RevDistanceDriver");
  }
  m_pDistance->SetAutomaticMode(true);
  m_pDistance->SetEnabled(true);
}

void RevDistanceDriver::DisableInit()
{
  m_pDistance->SetAutomaticMode(false);
  m_pDistance->SetEnabled(false);
}

double RevDistanceDriver::GetDistance()
{
  bool isValid = m_pDistance->IsRangeValid();
  if (isValid)
  {
    //For debugging and checking
    frc::SmartDashboard::PutNumber("DistanceSens Range", m_pDistance->GetRange());
    //frc::SmartDashboard::PutNumber("DistanceSens Timestamp", m_pDistance->GetTimestamp());
    //The current measured range is returned from GetRange(). By default
    // this range is returned in inches. I switched it from inches to millimeters for preference -Zach
    return (double)m_pDistance->GetRange();
  }
  else
  {
    //Util::SendErrorAndCode("Distance Sensor Range Invalid", 133, "DistanceSensorDriver.cpp");
    return -1.0;
  }
}

bool RevDistanceDriver::IsRangeValid()
{
  frc::SmartDashboard::PutBoolean("DistanceSens RangeValid?", m_pDistance->IsRangeValid());
  return m_pDistance->IsRangeValid();
}

double RevDistanceDriver::GetMeasurementInMM()
{
    //Returns value in milimeters
  return m_pDistance->GetRange(rev::Rev2mDistanceSensor::DistanceUnit::kMilliMeters);
}
