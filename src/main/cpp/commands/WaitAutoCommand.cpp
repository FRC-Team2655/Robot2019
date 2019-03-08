/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/WaitAutoCommand.h"

WaitAutoCommand::WaitAutoCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void WaitAutoCommand::Initialize() {
  if (startedFromAutoManager) {
    SetTimeout(stod(arguments[0]));
  }else{
    SetTimeout(0);
  }
}

// Called repeatedly when this Command is scheduled to run
void WaitAutoCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool WaitAutoCommand::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void WaitAutoCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitAutoCommand::Interrupted() {
  End();
}
