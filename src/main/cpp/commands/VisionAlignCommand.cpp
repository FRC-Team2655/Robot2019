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
  if(std::abs(Robot::visionManager.getRelativeTapeHeading()) <= 2) {
    End();
    return; 
  }
  if(Robot::visionManager.isTapeDetected()){
    heading = Robot::driveBase.getIMUAngle() + Robot::visionManager.getRelativeTapeHeading();
    Robot::driveBase.enableRotatePID(heading, true);
  }else{
    End();
  }
  SetTimeout(1.1);
}

// Called repeatedly when this Command is scheduled to run
void VisionAlignCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool VisionAlignCommand::IsFinished() {
  if(quit)
    return true;

  if(std::abs(Robot::driveBase.getIMUAngle() - heading) < 1.5)
      stopCounter++;
  else
    stopCounter = 0;

  return stopCounter >= 3 || IsTimedOut();
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
