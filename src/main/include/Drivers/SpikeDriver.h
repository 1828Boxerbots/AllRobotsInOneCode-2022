/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Relay.h>

class SpikeDriver
{
public:
    SpikeDriver(int port);

    void TurnSpikeOn();
    void TurnSpikeOff();

    frc::Relay::Value GetState();

    //bool StatusIsFatal() { return m_pDevice->StatusIsFatal(); }

private:
    frc::Relay *m_pDevice = nullptr;
};

// 2/14/20
