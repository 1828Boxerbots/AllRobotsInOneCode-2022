/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/CameraDrivers/CameraDeviceDriver.h"

CameraDeviceDriver::CameraDeviceDriver(int index) 
{
    m_index = index;
}

bool CameraDeviceDriver::Init()
{
    m_USBcamera = cs::UsbCamera("USB Camera", m_index);
    // if(m_CVcamera.open(0))
    // {
    //     return false;
    // }
    return true;
}

void CameraDeviceDriver::DisplayCamera()
{
    m_USBcamera = frc::CameraServer::GetInstance() -> StartAutomaticCapture();
    m_USBcamera.SetResolution(640, 480);
}

double CameraDeviceDriver::WhereToTurn(double deadZone)
{
    //Check if there is a blob
    if (GetBlob() == false)
    {
        return -2.0;
    }

    Util::Log("Camera CentroidX", m_centroidX);
    Util::Log("Camera CentroidY", m_centroidY);

    //Get center of screen
    double screenCenter = m_frame.size().width / 2;

    //Deadzone values
    double highDedZone = screenCenter + deadZone;
    double lowDedZone = screenCenter - deadZone;

    //Check Deadzone
    if (m_centroidX > lowDedZone && m_centroidX < highDedZone)
    {
        return 0.0;
    }

    //Use MATH to turn the centroid into a precentage and return
    double powerPercentage = (m_centroidX - screenCenter) / screenCenter;
    Util::Log("Power Percentage", powerPercentage);

    return powerPercentage;
}

bool CameraDeviceDriver::GetBlob()
{
    //Gets frame from camera and set m_frame
    

    //Filter the image


    //Checks if there is a blob
}

void CameraDeviceDriver::SetColor()
{
    //Change camerea value from BGR to HSV


    //Looks for specifc colors


    //Find moments of the image


}