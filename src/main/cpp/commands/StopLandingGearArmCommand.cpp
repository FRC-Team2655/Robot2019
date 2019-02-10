/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StopLandingGearArmCommand.h"
#include <Robot.h>

StopLandingGearArmCommand::StopLandingGearArmCommand() {
  Requires(&Robot::landingGearArm);
}

// Called just before this Command runs the first time
void StopLandingGearArmCommand::Initialize() {
  Robot::landingGearArm.stopArm();
}

// Called repeatedly when this Command is scheduled to run
void StopLandingGearArmCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool StopLandingGearArmCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void StopLandingGearArmCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopLandingGearArmCommand::Interrupted() {}
