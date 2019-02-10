/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveLandingGearCommand.h"
#include <Robot.h>

MoveLandingGearCommand::MoveLandingGearCommand(double value, bool positionMode) : value(value), positionMode(positionMode) {
  Requires(&Robot::landingGearArm);
}

// Called just before this Command runs the first time
void MoveLandingGearCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MoveLandingGearCommand::Execute() {
  if(positionMode)
    Robot::landingGearArm.moveArmPosition(value);
  else
    Robot::landingGearArm.moveArmSpeed(value);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveLandingGearCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void MoveLandingGearCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveLandingGearCommand::Interrupted() {}
