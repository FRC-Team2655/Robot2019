/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootersPercetnageCommand.h"

ShootersPercetnageCommand::ShootersPercetnageCommand() {
  Requires(&Robot::ballShooter);
}

// Called just before this Command runs the first time
void ShootersPercetnageCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ShootersPercetnageCommand::Execute() {
  Robot::ballShooter.MoveTalonSpeed(0);
}

// Make this return true when this Command no longer needs to run execute()
bool ShootersPercetnageCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void ShootersPercetnageCommand::End() {
  Robot::ballShooter.MoveTalonSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootersPercetnageCommand::Interrupted() {}
