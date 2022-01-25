/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrainSubsystemBase.h"
#include <math.h>

DriveTrainSubsystemBase::DriveTrainSubsystemBase() {}

// This method will be called once per scheduler run
void DriveTrainSubsystemBase::Periodic() {}

void DriveTrainSubsystemBase::MoveTank(double leftY, double rightY)
{
    GyroGetAngle();
    GetRightEncoderInch();
    GetLeftEncoderInch();
    leftY = Util::Limit(leftY);
    rightY = Util::Limit(rightY);
    if (leftY > 0.1 || leftY < -0.1)
    {
        GetLeftEncoderInch();
    }
    if (rightY > 0.1 || rightY < -0.1)
    {
        GetRightEncoderInch();
    }
    frc::SmartDashboard::PutNumber("Drive Left", leftY);
    frc::SmartDashboard::PutNumber("Drive Right", rightY);

    //Lidar returns 0 if object is out of distance, minimum distance is to prevent an infinite loop
    //implemented solely for lidar, will change later for distance sensors
    if (GetLidarDetectionDistance() > MINIMUMDISTANCE && m_hasAntiCollision == true)
    {
        //If turning, since sensor is generally on front, keep turning
        if (leftY < -0.1 || rightY < -0.1)
        {
            SetMotorL(leftY);
            SetMotorR(rightY);
        }
        //Again, if turning,but object is within collision range, still turn, but if not turning, then set motors to stop
        else if (GetLidarDetectionDistance() < m_lidarCollisionDistance)
        {
            if (leftY < -0.1 || rightY < -0.1)
            {
                SetMotorL(leftY);
                SetMotorR(rightY);
            }
            else
            {
                SetMotorL(0.0);
                SetMotorR(0.0);
            }
        }
        // If object is not within collision range, just continue with driving
        else
        {
            SetMotorL(leftY);
            SetMotorR(rightY);
        }
    }
    //If no object is within range of lidar's distance or anti collision isn't active, then just continue with driving
    else
    {
        SetMotorL(leftY);
        SetMotorR(rightY);
    }
    //This is for distance sensor implementation, if distance sensor doesn't pick up anything, then go on with code
    if (IsDistanceLeftActive() == true && m_hasAntiCollision == true)
    {
        //Distance less than collision range
        if (GetDistanceSensorDetectionDistanceLeft() < m_distanceCollisionDistanceLeft)
        {
            //If turning right,forward, or reverse, continue moving
            if ((leftY > 0.1 && rightY < -0.1) || (leftY > 0.1 && rightY > 0.1) || (leftY < -0.1 && rightY < -0.1))
            {
                SetMotorL(leftY);
                SetMotorR(rightY);
            }
            //If not turning, set motors to 0
            else
            {
                SetMotorL(0.0);
                SetMotorR(0.0);
            }
        }
    }
    if (IsDistanceRightActive() == true && m_hasAntiCollision == true)
    {
        //Distance less than collision range
        if (GetDistanceSensorDetectionDistanceRight() < m_distanceCollisionDistanceRight)
        {
            //If turning left,moving forward, or reversing, continue moving
            if (((leftY < -0.1) && (rightY > 0.1)) || ((leftY > 0.1) && (rightY > 0.1)) || ((leftY < -0.1) && (rightY < -0.1)))
            {
                SetMotorL(leftY);
                SetMotorR(rightY);
            }
            //If not going reverse, set motors to 0
            else
            {
                SetMotorL(0.0);
                SetMotorR(0.0);
            }
        }
    }
}

void DriveTrainSubsystemBase::MoveArcade(double Y, double X)
{
    double m_scale = 1;
    double leftY = Y + X;
    double rightY = Y - X;
    //MoveTank(leftY, rightY * m_scale); //TeleOp Test
    SetMotorL(leftY);
    SetMotorR(rightY * m_scale);

}

void DriveTrainSubsystemBase::IMUArcade(double y, double x, double angle)
{
    double m_scale = 1;
    double leftY = y + x;
    double rightY = y - x;
    frc::SmartDashboard::PutNumber("Shadow", 1);
    double currentAngle = IMUGetAngle();
    double startAngle = IMUGetAngle();
    frc::SmartDashboard::PutNumber("Shadow", 2);
    if(angle < 0)
    {
        while (currentAngle - startAngle > angle)
        {
            frc::SmartDashboard::PutNumber("Shadow", 3);
            MoveTank(leftY, rightY * m_scale);
            currentAngle = IMUGetAngle();
        }    
    }

    else if ( angle > 0)
    {
        while (currentAngle - startAngle < angle)
        {
            frc::SmartDashboard::PutNumber("Shadow", 3);
            MoveTank(leftY, rightY * m_scale);
            currentAngle = IMUGetAngle();
        }
    }
    
    frc::SmartDashboard::PutNumber("Shadow", 4);
    Stop();
}

void DriveTrainSubsystemBase::ArcadeVision(double y, double x, OldCameraVision::VisionColors color)
{
    double m_scale = 0.0;
    double leftY = y + x;
    double rightY = y - x;

    double deadZoneLocation = 0.75;
    double deadZoneRange = 30;

    SetLookingColorV(color);

    SetLookingColorV(OldCameraVision::VisionColors::GREEN_CONE_N);

    double turn =  WhereToTurn(deadZoneLocation, deadZoneRange);

    
    while(turn > -2.9)
    {
        MoveTank(leftY, rightY * m_scale);
        turn =  WhereToTurn(deadZoneLocation, deadZoneRange);
    }
    Stop();
}

void DriveTrainSubsystemBase::TimedArcade(double y, double x, units::second_t time)
{
     m_autoTimer.Stop();
    m_autoTimer.Reset();
    m_autoTimer.Start();
    units::second_t startTime = m_autoTimer.Get();
    do
    {
        MoveArcade(y, x);
    } while (time > m_autoTimer.Get()-startTime);
    Stop();
}

void DriveTrainSubsystemBase::TurnRight(double speed)
{
    if(speed < 0)
    {
        speed = -speed;
    }
    MoveTank(speed, -speed*1.28);
}

void DriveTrainSubsystemBase::TurnLeft(double speed)
{
    if(speed < 0)
    {
        speed = -speed;
    }
    MoveTank(-speed, speed*1.28);
}

void DriveTrainSubsystemBase::LogEncoder()
{
    frc::SmartDashboard::PutNumber("Right Encoder Distance", m_rightEncoderSim);
    frc::SmartDashboard::PutNumber("Left Encoder Distance", m_leftEncoderSim);
}

//Stops robot
void DriveTrainSubsystemBase::Stop()
{
    MoveTank(0.0, 0.0);
}

//Moves robot forward
void DriveTrainSubsystemBase::Forward(double speed)
{
    MoveTank(speed , speed);
}

bool DriveTrainSubsystemBase::MoveAlignPID(double targetDistance, double heading, double maxSpeed)
{
    //
    //Distance
    //

    // Get Encoder values [Inches]
    double leftEncoder = GetLeftEncoderInch();
    double rightEncoder = GetRightEncoderInch();

    // If an encoder fails, we assume that it stops generating pulses
    // so use the larger of the two (absolute distance)
    double encoderDistance;
    if (std::abs(leftEncoder) > std::abs(rightEncoder))
    {
        encoderDistance = leftEncoder;
    }
    else
    {
        encoderDistance = rightEncoder;
    }

    // Get Control Loop Period
    units::second_t loopTime = LOOPTIME;

    double error = targetDistance - encoderDistance;

    // Linear-Proportional control

    // Linear-Integral control
    if (error < m_deadZone)
    {
        m_sumError += error / (double)loopTime;
    }
    else
    {
        m_sumError = 0;
    }

    // Linear-Derivative control
    double dError = (error - m_preError) / (double)loopTime;

    double lin = (m_kP * error) + (m_kI * m_sumError) + (m_kD * dError);

    m_preError = error;

    // Ramp up to speed to reduce wheel slippage
    double max_ramp_up = 0.075;
    if (lin > m_preLin + max_ramp_up)
    {
        lin = m_preLin + max_ramp_up;
    }
    m_preLin = lin;

    // Limit max speed
    lin = Util::AbsMax(lin, maxSpeed);

    //
    // Rotation
    //

    m_kP_rot = maxSpeed / m_slowAngle; //Start slowing down at X degree
    double errorRotation = heading - (double)GyroGetAngle();
    double rotation = errorRotation * m_kP_rot;

    //Max Rotation Speed
    rotation = Util::AbsMax(rotation, maxSpeed);

    //Nothing left but to for it...
    MoveArcade(lin, rotation);

    //Determine if the robot made it to the target
    //and then wait a bit so that it can be correct any overshoot.
    if (error > 2 || errorRotation > 3.0)
    {
        m_autoTimer.Reset();
    }
    else if (m_autoTimer.Get() > 0.75_s)
    {
        return true;
    }

    //Keep trying...
    return false;
}

void DriveTrainSubsystemBase::FixRotation(units::degree_t wantedAngle, double speed)
{
    units::degree_t currentAngle = GyroGetAngle();
    while (currentAngle != wantedAngle)
    {
        currentAngle = GyroGetAngle();
        if (currentAngle > wantedAngle)
        {
            TurnRight(speed);
        }
        else
        {
            TurnLeft(speed);
        }
    }
    Stop();
}

//Pretty buggy, two versions of it: PIDS control and regular control. PIDS makes sure the robot is straight, regular just moves forward
void DriveTrainSubsystemBase::ForwardInInch(double inch, double angle, double speed)
{
    WhereToTurn(-0.7, 40);

    ResetEncoder();
    //This is Regular
    double startDistanceRight = GetRightEncoderInch();
    double currentDistanceRight = GetRightEncoderInch();
    double startDistanceLeft = GetLeftEncoderInch();
    double currentDistanceLeft = GetLeftEncoderInch();

    double startDistanceRightRaw = GetLeftEncoderRaw();
    double currentDistanceRightRaw = GetRightEncoderRaw();
    double startDistanceLeftRaw = GetLeftEncoderRaw();
    double currentDistanceLeftRaw = GetLeftEncoderRaw();

    double multiplierR = 0.0;
    double SPEED_INCREMENT = 0.005;
    double ENCODER_DEADZONE = 40;
    while ((Util::Abs(currentDistanceLeft - startDistanceLeft) < inch))
        // || (Util::Abs(currentDistanceRight - startDistanceRight) < inch))
    {
        //Forward(speed);
        Util::Log("Right Multiplier", multiplierR, "DriveTrainSubsystemBase");
        MoveTank(speed,speed*multiplierR);
        Util::DelayInSeconds(0.02_s);
        Util::Log("Start Distance Right", startDistanceRightRaw, "DriveTrainSubsystemBase");
        Util::Log("Start Distance Left", startDistanceLeftRaw, "DriveTrainSubsystemBase");
        Util::Log("Delta Right", (-currentDistanceRightRaw)-(-startDistanceRightRaw), "DriveTrainSubsystemBase");
        Util::Log("Delta Left", currentDistanceLeftRaw-startDistanceLeftRaw, "DriveTrainSubsystemBase");
        currentDistanceRight = GetRightEncoderInch();
        currentDistanceLeft = GetLeftEncoderInch();
        currentDistanceRightRaw = GetRightEncoderRaw();
        currentDistanceLeftRaw = GetLeftEncoderRaw();
        if(Util::Abs(currentDistanceRightRaw-startDistanceRightRaw)<Util::Abs(currentDistanceLeftRaw-startDistanceLeftRaw)-ENCODER_DEADZONE)
        {
            multiplierR += SPEED_INCREMENT;
        }
        else if(Util::Abs(currentDistanceRightRaw-startDistanceRightRaw)>Util::Abs(currentDistanceLeftRaw-startDistanceLeftRaw)+ENCODER_DEADZONE)
        {
            multiplierR -= SPEED_INCREMENT;
        }
        if(speed*multiplierR>1.0)
        {
            multiplierR -= SPEED_INCREMENT;
        }
        else if(speed*multiplierR<-1.0)
        {
            multiplierR += SPEED_INCREMENT;
        }
    }
    if (currentDistanceLeft > inch)
    {
        ResetEncoder();
    }
    Stop();
}

//Used to turn the robot a certain amount of degrees(RelativeAngle is user's wanted angle)
 void DriveTrainSubsystemBase::TurnInDegreesGyro(double relativeAngle, double speed)
 {
     //troubleshooting values, use these for testing what makes the robot go to the relative angle
     frc::SmartDashboard::PutNumber("Current Angle", relativeAngle);
     frc::SmartDashboard::PutBoolean("In Place", true);
     double startAngle = IMUGetAngle();
     double currentAngle = IMUGetAngle();
     //logic used to turn the robot left or right and keeping it turned
     if (relativeAngle > 0)
     {
         TurnRight(speed);
         while (currentAngle - startAngle < relativeAngle)
         {
            currentAngle = IMUGetAngle();
         }
     }
     if (relativeAngle < 0)
     {
         TurnLeft(speed);
         while (currentAngle - startAngle > relativeAngle)
         {
            currentAngle = IMUGetAngle();
         }
     }
     Stop();
 }

//Used to turn the robot a certain amount of degrees(RelativeAngle is user's wanted angle)
void DriveTrainSubsystemBase::TurnInDegrees(double relativeAngle, double speed, double turnRadius)
{
    //This is Regular
    ResetEncoder();
    double startDistance = GetLeftEncoderInch();
    double currentDistanceLeft = GetLeftEncoderInch();
    double inch = Util::Abs(relativeAngle)*(Util::PI/180)*turnRadius;
    while (Util::Abs(currentDistanceLeft - startDistance) < inch )
    {
        if(relativeAngle < 0)
        {
            TurnLeft(speed);
        }
        else
        {
            TurnRight(speed);
        }
        currentDistanceLeft = GetLeftEncoderInch();
        frc::SmartDashboard::PutNumber("LeftEncoderInches", GetLeftEncoderInch());
        Util::Log("DriveTrainSubsystemBase: TurnInDegrees: current", currentDistanceLeft);
        Util::Log("DriveTrainSubsystemBase: TurnInDegrees: start", startDistance);
        Util::Log("DriveTrainSubsystemBase: TurnInDegrees: inch", inch);
    }
    Stop();
}

void DriveTrainSubsystemBase::Init()
{
    GyroInit();
    Init();
}

//function used to turn the robot in seconds; Use at your own risk
void DriveTrainSubsystemBase::ForwardInSeconds(double goalTime, double speed)
{
    m_autoTimer.Stop();
    m_autoTimer.Reset();
    m_autoTimer.Start();
    units::second_t startTime = m_autoTimer.Get();
    do
    {
        Forward(speed);
    } while (goalTime > (double)m_autoTimer.Get()-(double)startTime);
    Stop();
}

void DriveTrainSubsystemBase::AlignWithVision(double deadZoneLocation, int deadZoneRange, bool defaultTurnRight, bool forward)
{
    Util::Log("Direction", "Null");
    double turn =  WhereToTurn(deadZoneLocation, deadZoneRange);
    while(turn != 0.0)
    {
        Util::DelayInSeconds(0.3_s);
        turn = WhereToTurn(deadZoneLocation, deadZoneRange);
        if(turn < -1.0)
        {
                Util::Log("Direction", "No See");
            //Turn right/left if object is not seen
            if(defaultTurnRight == true)
            {
                TurnRight(0.15);
                Util::DelayInSeconds(0.1_s);
                Stop();
            }
            else if(defaultTurnRight == false)
            {
                TurnLeft(0.15);
                Util::DelayInSeconds(0.1_s);
                Stop();
            }
        }
        else if (turn < 0.0)
        {
            Util::Log("Direction", "TurnLeft");
            //Turn left if object is on the left
            TurnLeft(0.15);
            Util::DelayInSeconds(0.05_s);
            Stop();
        }
        else if(turn > 0.0)
        {
            Util::Log("Direction", "TurnRight");
            //Turn right if object is on the right
            TurnRight(0.15);
            Util::DelayInSeconds(0.05_s);
            Stop();
        }
    }
    Util::Log("Direction", "Center");
    if(forward == true)
    {
        Forward(0.25);
        while(turn > -2.9)
        {
            //Continue Forwards until object is not see-able
            turn =  WhereToTurn(deadZoneLocation, deadZoneRange);
            Util::Log("TurnCam", turn);
        }
        Util::Log("Direction", "Stop");
    }
    Stop();
}

void DriveTrainSubsystemBase::MoveWithVision(double deadZoneLocation, int deadZoneRange, int moveSpeed, bool defaultTurnRight)
{
    double turn =  WhereToTurn(deadZoneLocation, deadZoneRange);
    while(turn != 0.0)
    {
        turn = WhereToTurn(deadZoneLocation, deadZoneRange);
        if(turn < -1.0)
        {
            //Turn right/left if object is not seen
            if(defaultTurnRight == true)
            {
                TurnRight(0.3);
            }
            else if(defaultTurnRight == false)
            {
                TurnLeft(0.3);
            }
        }
        else if (turn < 0.0)
        {
            //Move left if object is on the left
            MoveArcade(moveSpeed, -0.2);
        }
        else if(turn > 0.0)
        {
            //Turn right if object is on the right
            MoveArcade(moveSpeed, 0.2);
        }
        else
        {
            //Object is in the center
            MoveArcade(moveSpeed, 0.0);
        }
    }
}

double DriveTrainSubsystemBase::ReadIMU()
{
    return IMUGetAngle();
}

void DriveTrainSubsystemBase::ForwardInInches2(double inches, double speed)
{
    ResetEncoder();

    double rightInch = 0.0;
    double leftInch = 0.0;
    double rightInchStart = GetRightEncoderInch();
    double leftInchStart = GetLeftEncoderInch();
    double realSpeed = 0.0;
    double rightSpeed = realSpeed + 0.08;
    double deadZone = 0.001;

    int targetReached = 0;
    
    while(Util::Abs(leftInch - leftInchStart) < inches)
    {
        if(realSpeed<speed)
        {
            rightSpeed -= realSpeed;
            realSpeed += speed/10;
            rightSpeed += realSpeed;
        }

        Util::Log("Right Speed", rightSpeed, "DriveTrainSubsystemBase");
        Util::Log("Real Speed", realSpeed, "DriveTrainSubsystemBase");

        SetMotorL(realSpeed);
        SetMotorR(rightSpeed);

        leftInch = GetLeftEncoderInch();
        rightInch = GetRightEncoderInch();

        if ( (Util::Abs(leftInch - leftInchStart) > Util::Abs(rightInch - rightInchStart) + deadZone) && (targetReached < 200) )
        {
            rightSpeed += 0.00002;
        }
        else if( (Util::Abs(leftInch - leftInchStart) < Util::Abs(rightInch - rightInchStart) - deadZone) && (targetReached < 200) )
        {
            rightSpeed -= 0.00002;
        }
        else
        {
            Util::Log("Temp Working Speed Ratio", (rightSpeed/speed));
            targetReached++;
        }
    }
    Stop();
}

void DriveTrainSubsystemBase::ForwardInInchGyro(double inch, double speed, double angleDeadZone, double turnSpeed)
{
    ResetEncoder();

    double startAngle = IMUGetAngle();
    double currentAngle = IMUGetAngle();

    Util::Log("ForwardGyro SA", startAngle);

    double rightInch = 0.0;
    double leftInch = 0.0;
    double rightInchStart = GetRightEncoderInch();
    double leftInchStart = GetLeftEncoderInch();

    double deadZone = angleDeadZone;
    //double deadZoneInch = 0.1;

    double startAngleLow = startAngle - deadZone;
    double startAngleHigh = startAngle + deadZone;

    double howToTurn = 0;
    
    while(Util::Abs(leftInch - leftInchStart) < inch || Util::Abs(rightInch - rightInchStart) < inch)
    {
        if(currentAngle > startAngleHigh)
        {
            //Turn Right
            howToTurn = turnSpeed;
        }
        else if(currentAngle < startAngleLow)
        {
            //Turn Left
            howToTurn = -turnSpeed;
        }
        else
        {
            //DONT TURN FOOL
            howToTurn = 0;
        }

        leftInch = GetLeftEncoderInch();
        rightInch = GetLeftEncoderInch();

        currentAngle = IMUGetAngle();

        Util::Log("ForwardGyro CA", currentAngle);

        MoveArcade(speed, howToTurn);
    }

    Stop();
}

void DriveTrainSubsystemBase::RotateToDegreeAbsolute(double degree, double speed, double deadZone)
{
    double currentAngle = IMUGetAngle();
  
    double lowerDegree = degree - deadZone;
    double upperDegree = degree + deadZone;

    while(currentAngle > upperDegree || currentAngle < lowerDegree)
    {
        if(currentAngle > upperDegree)
        {
            TurnRight(speed);
        }
        else if(currentAngle < lowerDegree)
        {
            TurnLeft(speed);
        }
        currentAngle = IMUGetAngle();
    }

    Stop();
}