/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ExtendClawCommand.h"
#include <Robot.h>

ExtendClawCommand::ExtendClawCommand(bool shouldExtend) : shouldExtend(shouldExtend) {
}

// Called just before this Command runs the first time
void ExtendClawCommand::Initialize() {

  std::transform(commandName.begin(), commandName.end(), commandName.begin(), ::toupper);

  if (startedFromAutoManager && commandName == "EXTEND_CLAW") {
    shouldExtend = true;
  }else if (startedFromAutoManager && commandName == "RETRACT_CLAW") {
    shouldExtend = false;
  }

  if (shouldExtend) {
    Robot::hatchPanelClaw.extendClaw();
  }else{
    Robot::hatchPanelClaw.retractClaw();
  }
}

// Called repeatedly when this Command is scheduled to run
void ExtendClawCommand::Execute() {
  std::cout << "Extending claw..." << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendClawCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ExtendClawCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendClawCommand::Interrupted() {
  End();
}
