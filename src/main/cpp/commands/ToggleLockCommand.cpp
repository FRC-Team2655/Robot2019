/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleLockCommand.h"
#include <commands/LandingGearArmTimeCG.h>
#include <Robot.h>
#include <iostream>

ToggleLockCommand::ToggleLockCommand() {
  Requires(&Robot::landingGearArm);
}

// Called just before this Command runs the first time
void ToggleLockCommand::Initialize() {
  if(Robot::landingGearArm.isLocked()){
    Robot::landingGearArm.unlock();
  }else{
    Robot::landingGearArm.lock();
  }
}

// Called repeatedly when this Command is scheduled to run
void ToggleLockCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ToggleLockCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ToggleLockCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleLockCommand::Interrupted() {}
