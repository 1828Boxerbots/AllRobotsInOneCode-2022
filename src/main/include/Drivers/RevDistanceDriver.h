// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #pragma once

// #include "DriverUtil/DistanceSensorSource.h"
#include "Util.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "rev/Rev2mDistanceSensor.h"

class RevDistanceDriver
{
public:
  RevDistanceDriver(rev::Rev2mDistanceSensor::Port port = rev::Rev2mDistanceSensor::Port::kOnboard,
                          rev::Rev2mDistanceSensor::DistanceUnit unit = rev::Rev2mDistanceSensor::DistanceUnit::kMilliMeters,
                          rev::Rev2mDistanceSensor::RangeProfile profile = rev::Rev2mDistanceSensor::RangeProfile::kDefault);

  void Init(bool log = false);
  void DisableInit();

 double GetMeasurementInMM();
 double GetDistance();

  bool IsRangeValid();
  //bool StatusIsFatal() { return m_pDistance->StatusIsFatal(); }

private:
  rev::Rev2mDistanceSensor *m_pDistance = nullptr;
};

// Finished 2/17/20. Untested
