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

  if(startedFromAutoManager){
    if(arguments.size() < 1){
      heading = Robot::driveBase.getIMUAngle();
    }else{
      heading = std::stod(arguments[0]);
    }
  }
}

// Called just before this Command runs the first time
void RotateCommand::Initialize() {
  Robot::driveBase.enableRotatePID(heading);
  SetTimeout(2);
}

// Called repeatedly when this Command is scheduled to run
void RotateCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool RotateCommand::IsFinished() { 
  
  if(std::abs(Robot::driveBase.getIMUAngle() - heading) <= 1)
    stopCounter++;
  else
    stopCounter = 0;
  

  return stopCounter >= 20 || IsTimedOut();
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
