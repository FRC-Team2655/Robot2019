/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RotateCommand.h"

#include <Robot.h>

RotateCommand::RotateCommand(double heading) : heading(heading) {
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void RotateCommand::Initialize() {
  if(startedFromAutoManager){
    if(arguments.size() < 1){
      this->heading = Robot::driveBase.getIMUAngle();
    }else{
      this->heading = std::stod(arguments[0]);
    }
  }

  lastHeading = Robot::driveBase.getIMUAngle();
  Robot::driveBase.enableRotatePID(heading);
  SetTimeout(2);
}

// Called repeatedly when this Command is scheduled to run
void RotateCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool RotateCommand::IsFinished() { 
  
  if(std::abs(Robot::driveBase.getIMUAngle() - heading) <= 3)
    stopCounter++;
  else{
    stopCounter = 0;
  }

  double h = Robot::driveBase.getIMUAngle();
  if((std::abs(h - lastHeading) < 2) && (std::abs(Robot::driveBase.getIMUAngle() - heading) <= 7)){
    headingChangeCounter++;
  }else{
    headingChangeCounter = 0;
  }
  lastHeading = h;
  
  return (stopCounter >= 12) || (headingChangeCounter >= 5) || IsTimedOut();
}

// Called once after isFinished returns true
void RotateCommand::End() {
  Robot::driveBase.disableRotatePID();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateCommand::Interrupted() {
  End();
}
