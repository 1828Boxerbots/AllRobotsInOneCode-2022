/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/*
#include "subsystems/CameraSubsystemBase.h"
#include "Constants.h"
#include "subsystems/DriveTrainSubsystemBase.h"
#include <cameraserver/CameraServer.h>


CameraSubsystemBase::CameraSubsystemBase(DriveTrainSubsystemBase *pDrive) 
{
    m_pDriveObject = pDrive;
}


void CameraSubsystemBase::Init()
{
    if (m_isInitialized == true)
    {
        return;
    }
    frc::SmartDashboard::PutBoolean("ready to send image", true);
    InitSendImage();
    
    m_isInitialized = true;
}


void CameraSubsystemBase::SetColor(int colorNumber)
{
    if (m_isInitialized == false) 
    {
        return;
    }
    switch (colorNumber)
    {
    case 0:
        cv::inRange(m_frame,  
            cv::Scalar(GREEN_LOW_BLUE, GREEN_LOW_GREEN, GREEN_LOW_RED),
            cv::Scalar(GREEN_HIGH_BLUE, GREEN_HIGH_GREEN, GREEN_HIGH_RED), m_colorFilter);
        break;
    case 1:
        cv::inRange(m_frame, 
            cv::Scalar(YELLOW_LOW_BLUE, YELLOW_LOW_GREEN, YELLOW_LOW_RED),
            cv::Scalar(YELLOW_HIGH_BLUE, YELLOW_HIGH_GREEN, YELLOW_HIGH_RED), m_colorFilter);
        break;
    default:
        break;
    }
    //BGR
}


void CameraSubsystemBase::FilterFrame()
{
    if (m_isInitialized == false) 
    {
        return;
    }
    
    //SetColor(YELLOW_FILTER);
    
    cv::morphologyEx(m_colorFilter, m_openFilter, cv::MORPH_OPEN, m_morph, cv::Point(-1, -1), 4);
    cv::dilate(m_openFilter,m_dilution,m_morph);
    cv::morphologyEx(m_dilution, m_output, cv::MORPH_CLOSE, m_morph, cv::Point(-1,-1),4);

    m_moment = cv::moments(m_output);
    m_center = cv::Point2f(m_moment.m10 / m_moment.m00, m_moment.m01 / m_moment.m00);

    if(m_center.x == 0 && m_center.y == 0)
    {
        m_defaultCenter = m_defaultCenter;
    }
    else
    {
        m_defaultCenter = m_center;
    }

    
}


void CameraSubsystemBase::VideoThread(CameraSubsystemBase* pCamera)
{
    
    if(pCamera != nullptr)
    {
        pCamera->TeleopImage();
    }
}


void CameraSubsystemBase::TeleopImage()
{
   
    if (m_isInitialized == false)
    {
        return;
    }
    frc::CameraServer::StartAutomaticCapture();
    m_cvSink = frc::CameraServer::GetVideo();
    m_outputStream = frc::CameraServer::PutVideo("Rectangle",640,480);
    cv::Mat output;
    while(m_stopSendImage == false)
    {
        if (m_cvSink.GrabFrame(m_frame) == 0)
        {
            m_outputStream.NotifyError(m_cvSink.GetError());
            continue;
        }
        FilterFrame();
        double blobWidth = 50;
        double blobHeight = 50;

        cv::resize(m_frame,output,cv::Size(),1.0, 1.0);
        cv::rectangle(output, 
            cv::Rect2d(
                cv::Point(m_defaultCenter.x+blobWidth/2, m_defaultCenter.y + blobHeight/2),
                cv::Point(m_defaultCenter.x-blobWidth/2, m_defaultCenter.y - blobHeight/2)),
            cv::Scalar(0,0,255), 3);    
        m_outputStream.PutFrame(output);
    }
    
}


void CameraSubsystemBase::InitSendImage()
{   

    std::thread videoThread(VideoThread,this);
    videoThread.detach();

    
   
}


// This method will be called once per scheduler run
void CameraSubsystemBase::Periodic() 
{
    //CameraPeriodic();
}


void CameraSubsystemBase::CameraPeriodic()
{
    m_frameNumber++;
    frc::SmartDashboard::PutNumber("Camera Frame Number", m_frameNumber);
    
}


//Loop that turns the robot based on camera input
void CameraSubsystemBase::AutoCameraTurn()
{
    
    frc::SmartDashboard::PutBoolean("CameraWork", false);
    int dir;
    m_frameNumber++;
    frc::SmartDashboard::PutNumber("CameraWork frameNum", m_frameNumber);
    do
    {
        frc::SmartDashboard::PutBoolean("Camera Break", false);
        frc::SmartDashboard::PutNumber("Code Broke", false);
        frc::SmartDashboard::PutNumber("Shadow", 1);
        dir = WhereToTurn();
        frc::SmartDashboard::PutNumber("Shadow", 2);
        m_frameNumber++;
        frc::SmartDashboard::PutNumber("CameraWork frameNum", m_frameNumber);
        if(dir == 0)
        {
            frc::SmartDashboard::PutBoolean("Camera Break", true);
            break;
        }
        frc::SmartDashboard::PutNumber("Shadow", 3);
        if (dir == 1) 
        {
            frc::SmartDashboard::PutNumber("Shadow", 4);
            m_pDriveObject->TurnRight();
            frc::SmartDashboard::PutNumber("Shadow", 5);
        }
        if (dir == -1) 
        {
            frc::SmartDashboard::PutNumber("Shadow", 6);
            m_pDriveObject->TurnLeft();
            frc::SmartDashboard::PutNumber("Shadow", 7);
        }
        if(dir == -2)
        {
            m_pDriveObject->TurnLeft();
            frc::SmartDashboard::PutNumber("Shadow", 9.5);
        }
        if(dir != -1 && dir != 1 && dir == -2) 
        {
            frc::SmartDashboard::PutNumber("Shadow", 8);
            m_pDriveObject->TurnLeft(); 
            frc::SmartDashboard::PutBoolean("CodeBroke", true);
            frc::SmartDashboard::PutNumber("Shadow", 9);
        }
        frc::SmartDashboard::PutNumber("Camera Direction", dir);
        if(dir == 0)
        {
            frc::SmartDashboard::PutBoolean("Camera Break", true);
            break;
        }
    } while(dir != 0);
    frc::SmartDashboard::PutNumber("Shadow", 10);
    frc::SmartDashboard::PutBoolean("CameraWork", true);
}


int CameraSubsystemBase::WhereToTurn()
{
    //Log("centerX", m_center.x);
    //Log("maxRes", GetMaxResolutionX());

    frc::SmartDashboard::PutNumber("CodeRun", false);
    frc::SmartDashboard::PutBoolean("ABC", false);
    if (m_isInitialized == false) 
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Not initialized");
        frc::SmartDashboard::PutBoolean("ABC", true);
        return CANT_FIND_IMAGE; 
    }
    if(m_center.x  >= GetCenterMin() && m_center.x  < GetCenterMax())
    //if(m_center.x  >= 0 && m_center.x  < GetMaxResolutionX())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Center");
        frc::SmartDashboard::PutBoolean("ABC", true);
        return STOP;
    }
    else if ( m_center.x >= GetLeftMin() && m_center.x <  GetLeftMax())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Left");
        frc::SmartDashboard::PutBoolean("ABC", true);
        return GO_LEFT;
    } 
    else if(m_center.x  >= GetRightMin() && m_center.x < GetRightMax())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Right");
        frc::SmartDashboard::PutBoolean("ABC", true);
        return GO_RIGHT;
    }
    else if (m_center.x < 0 || m_center.x > GetMaxResolutionX())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "CANT SEE");
        frc::SmartDashboard::PutBoolean("ABC", true);
        return CANT_FIND_IMAGE; 
    }
    frc::SmartDashboard::PutBoolean("ABC", true);
    frc::SmartDashboard::PutBoolean("CodeRun", true);
    return STOP;
}

*/


//COMMENTED OUT FOR RESTART PURPOSES. THIS IS A REFERENCE.
