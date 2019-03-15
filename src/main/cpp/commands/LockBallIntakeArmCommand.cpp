/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LockBallIntakeArmCommand.h"
#include <Robot.h>

LockBallIntakeArmCommand::LockBallIntakeArmCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void LockBallIntakeArmCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LockBallIntakeArmCommand::Execute() {
  Robot::ballIntakeArm.lockPosition();
}

// Make this return true when this Command no longer needs to run execute()
bool LockBallIntakeArmCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void LockBallIntakeArmCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LockBallIntakeArmCommand::Interrupted() {}
