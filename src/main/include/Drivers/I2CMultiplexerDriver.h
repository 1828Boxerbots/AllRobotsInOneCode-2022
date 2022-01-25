/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/I2C.h>

#include "Util.h"
#include "Constants.h"

class I2CMultiplexerDriver
{
public:
  I2CMultiplexerDriver(frc::I2C::Port i2cPort, int breakoutAddress = breakoutAddress_base);

  bool SetChannel(uint8_t channel, bool log = true);
  uint8_t GetChannel();

  //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

  std::string GetChannelName(uint8_t channel);

private:
  // This is the address of the multiplexer itself
  static const uint8_t breakoutAddress_base = 0x70;

  // Which sensor are we currently reading from?
  uint8_t m_current_channel;

  // This is the I2C object of the multiplexer
  frc::I2C *m_pDevice = nullptr;
};

// 2/14/20
