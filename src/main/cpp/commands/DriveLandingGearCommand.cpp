/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveLandingGearCommand.h"
#include <Robot.h>

DriveLandingGearCommand::DriveLandingGearCommand(double percentage) : percentage(percentage) {
  Requires(&Robot::landingGearDrive);
}

// Called just before this Command runs the first time
void DriveLandingGearCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveLandingGearCommand::Execute() {
  Robot::landingGearDrive.moveSpeed(percentage);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveLandingGearCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveLandingGearCommand::End() {
  Robot::landingGearDrive.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveLandingGearCommand::Interrupted() {
  End();
}
