/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RetractClawTimeCommand.h"
#include <Robot.h>

RetractClawTimeCommand::RetractClawTimeCommand(double sec) : sec(sec) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void RetractClawTimeCommand::Initialize() {
  SetTimeout(sec);
}

// Called repeatedly when this Command is scheduled to run
void RetractClawTimeCommand::Execute() {
  if(IsTimedOut()){
    Robot::hatchPanelClaw._retract_action();
    isDone = true;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool RetractClawTimeCommand::IsFinished() { return isDone; }

// Called once after isFinished returns true
void RetractClawTimeCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractClawTimeCommand::Interrupted() {}
