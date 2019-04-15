/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "VisionManager.h"

VisionManager::VisionManager(std::function<double()> getAngleFuncs) : ntInstance(nt::NetworkTableInstance::GetDefault()),
                                 chickenVisionTable(ntInstance.GetTable("ChickenVision")),
                                 getAngleFunc(getAngleFunc) {
    tapeDetectedEntry = chickenVisionTable.get()->GetEntry("tapeDetected");
    tapeYawEntry = chickenVisionTable.get()->GetEntry("tapeYaw");

    driveWantedEntry = chickenVisionTable.get()->GetEntry("Driver");
    tapeWantedEntry = chickenVisionTable.get()->GetEntry("Tape");
 
    videoTimestampEntry = chickenVisionTable.get()->GetEntry("VideoTimestamp");

    enableTape();
}

void VisionManager::setGetAngleFunc(std::function<double()> getAngleFunc){
    this->getAngleFunc = getAngleFunc;
}

void VisionManager::enableTape(){
    driverVisionOnly = false;
    tapeVision = true;

    driveWantedEntry.SetBoolean(driverVisionOnly);
    tapeWantedEntry.SetBoolean(tapeVision);
}

void VisionManager::enableDriverOnly(){
    driverVisionOnly = true;
    tapeVision = false;

    driveWantedEntry.SetBoolean(driverVisionOnly);
    tapeWantedEntry.SetBoolean(tapeVision);
}

bool VisionManager::isTapeDetected(){
    return tapeDetectedEntry.GetBoolean(false);
}

double VisionManager::getRelativeTapeHeading(){
    if(!tapeDetectedEntry.GetBoolean(false))
        return 0;
    return tapeYawEntry.GetDouble(0);
}

double VisionManager::getAbsoluteTapeHeading(){
    if(getAngleFunc == nullptr)
        return getRelativeTapeHeading();
    return getRelativeTapeHeading() + getAngleFunc();
}
