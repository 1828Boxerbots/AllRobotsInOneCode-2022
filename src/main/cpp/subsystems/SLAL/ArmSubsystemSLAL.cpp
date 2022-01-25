/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SLAL/ArmSubsystemSLAL.h"
#include <frc/smartdashboard/SmartDashboard.h>

ArmSubsystemSLAL::ArmSubsystemSLAL() {}

// This method will be called once per scheduler run

void ArmSubsystemSLAL::SetMotor(double speed)
{
#ifndef NOHW
   m_liftMotorOne.Set(speed);
   m_liftMotorTwo.Set(-speed);
#endif
}

double ArmSubsystemSLAL::GetMotor()
{
#ifndef NOHW
   return (m_liftMotorOne.Get() + m_liftMotorTwo.Get()) / 2.0;
#else
   return 0.0;
#endif
}

void ArmSubsystemSLAL::Raise(double speed)
{
   SetMotor(speed);
}

void ArmSubsystemSLAL::Lower(double speed)
{
   SetMotor(-speed);
}

bool ArmSubsystemSLAL::UpperLimitHit()
{
#ifndef NOHW
   return m_topSwitch.Get();
#else
   return false;
#endif
}

bool ArmSubsystemSLAL::LowerLimitHit()
{
#ifndef NOHW
   return m_bottomSwitch.Get();
#else
   return false;
#endif
}

int ArmSubsystemSLAL::GetPosition()
{
   if (UpperLimitHit() == true)
   {
      return HIGHEST_POS;
   }
   else if (LowerLimitHit() == true)
   {
      return LOWEST_POS;
   }
   else
   {
      return INVALID_POS;
   }
}

void ArmSubsystemSLAL::SetPosition(int pos)
{
   switch (pos)
   {
   case LOWEST_POS:
      SetMotor(-m_liftSpeed);
      while (LowerLimitHit() != true)
      {
         SetMotor(-m_liftSpeed);
      }
      StopMotor();
      break;

   case HIGHEST_POS:
      SetMotor(m_liftSpeed);
      while (UpperLimitHit() != true)
      {
         SetMotor(m_liftSpeed);
      }
      StopMotor();
      break;
   default:
      SetMotor(m_liftSpeed);
      while (UpperLimitHit() != true)
      {
         SetMotor(m_liftSpeed);
      }
      StopMotor();
      break;
   }
}