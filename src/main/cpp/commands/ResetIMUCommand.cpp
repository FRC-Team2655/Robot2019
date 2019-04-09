/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ResetIMUCommand.h"
#include <Robot.h>

ResetIMUCommand::ResetIMUCommand() {
}

// Called just before this Command runs the first time
void ResetIMUCommand::Initialize() {
  std::transform(commandName.begin(), commandName.end(), commandName.begin(), ::tolower);
  if (startedFromAutoManager && commandName == "reset_forward") {
    Robot::driveBase.resetIMUForward();
  }else if (startedFromAutoManager && commandName == "reset_reverse") {
    Robot::driveBase.resetIMUReverse();
  }
}

// Called repeatedly when this Command is scheduled to run
void ResetIMUCommand::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool ResetIMUCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ResetIMUCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetIMUCommand::Interrupted() {}
