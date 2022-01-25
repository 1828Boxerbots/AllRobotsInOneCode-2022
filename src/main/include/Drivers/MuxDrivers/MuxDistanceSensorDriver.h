// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #pragma once

// #include "../I2CMultiplexerDriver.h"
// #include "../RevDistanceSensorDriver.h"

// class MuxDistanceSensorDriver
// {
// public:
//   MuxDistanceSensorDriver(/*Rev2mDistanceSensor::Port Port,
//                           int adr, //tito was here*/
//                           I2CMultiplexerDriver &breakout,
//                           uint8_t breakoutChannel
//                           /*Rev2mDistanceSensor::DistanceUnit units = Rev2mDistanceSensor::DistanceUnit::kInches,
//                           Rev2mDistanceSensor::RangeProfile profile = Rev2mDistanceSensor::RangeProfile::kDefault*/);

//   void SetActive();
//   bool IsRangeValid();
//   double GetDistance();
//   bool StatusIsFatal();
//   void Init(bool isOn = false);

// private:
//   I2CMultiplexerDriver &m_breakout;
//   uint8_t m_breakoutChannel;
//   frc::I2C::Port m_i2cPort;
//   //RevDistanceSensorDriver *m_pDistanceSensor;
// };
