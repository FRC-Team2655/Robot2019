/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LockClawCommand.h"
#include <Robot.h>

LockClawCommand::LockClawCommand() {;
  Requires(&Robot::hatchPanelClaw);
}

// Called just before this Command runs the first time
void LockClawCommand::Initialize() {
  Robot::hatchPanelClaw.lock();
}

// Called repeatedly when this Command is scheduled to run
void LockClawCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool LockClawCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void LockClawCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LockClawCommand::Interrupted() {}
