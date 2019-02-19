/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveIntakeArmPercentageCommand.h"
#include <Robot.h>

MoveIntakeArmPercentageCommand::MoveIntakeArmPercentageCommand(double speed) : speed(speed) {
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void MoveIntakeArmPercentageCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void MoveIntakeArmPercentageCommand::Execute() {
  Robot::ballIntakeArm.moveArmSpeed(speed);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveIntakeArmPercentageCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void MoveIntakeArmPercentageCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveIntakeArmPercentageCommand::Interrupted() {
  End();
}
