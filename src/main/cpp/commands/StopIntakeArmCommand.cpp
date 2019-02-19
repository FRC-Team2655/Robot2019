/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StopIntakeArmCommand.h"
#include <Robot.h>

StopIntakeArmCommand::StopIntakeArmCommand() {
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void StopIntakeArmCommand::Initialize() {
  Robot::ballIntakeArm.stopArm();
}

// Called repeatedly when this Command is scheduled to run
void StopIntakeArmCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool StopIntakeArmCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void StopIntakeArmCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopIntakeArmCommand::Interrupted() {
  End();
}