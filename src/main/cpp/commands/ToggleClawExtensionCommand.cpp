/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleClawExtensionCommand.h"
#include <Robot.h>

ToggleClawExtensionCommand::ToggleClawExtensionCommand() {
  
}

// Called just before this Command runs the first time
void ToggleClawExtensionCommand::Initialize() {
  if(Robot::hatchPanelClaw.isExtended()){
    Robot::hatchPanelClaw.retractClaw();
  }else{
    Robot::hatchPanelClaw.extendClaw();
  }
}

// Called repeatedly when this Command is scheduled to run
void ToggleClawExtensionCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ToggleClawExtensionCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ToggleClawExtensionCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleClawExtensionCommand::Interrupted() {}
