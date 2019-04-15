/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionAlignCommand.h"
#include <Robot.h>
#include <commands/RotateCommand.h>

VisionAlignCommand::VisionAlignCommand() {
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void VisionAlignCommand::Initialize() {
  quit = false;
  stopCounter = 0;
  if(Robot::visionManager.isTapeDetected()){
    heading = Robot::driveBase.getIMUAngle() - Robot::visionManager.getRelativeTapeHeading();
    Robot::driveBase.enableRotatePID(heading, true);
  }else{
    End();
  }
  SetTimeout(0.8);
}

// Called repeatedly when this Command is scheduled to run
void VisionAlignCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool VisionAlignCommand::IsFinished() {
  if(quit)
    return true;

  double h = Robot::driveBase.getIMUAngle();
  if(std::abs(Robot::visionManager.getRelativeTapeHeading()) < 2 && std::abs(h - lastHeading) <= 2){
    headingStopCounter++;
  }else{
    headingStopCounter = 0;
  }
  lastHeading = h;

  return headingStopCounter >= 5 || stopCounter >= 5 || IsTimedOut();
}

// Called once after isFinished returns true
void VisionAlignCommand::End() {
  quit = true;
  Robot::driveBase.disableRotatePID();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionAlignCommand::Interrupted() {
  quit = true;
}
