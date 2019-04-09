/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveIntakeArmPercentageCmd.h"

#include <Robot.h>

MoveIntakeArmPercentageCmd::MoveIntakeArmPercentageCmd(double p, double t) : percentage(p), time(t) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void MoveIntakeArmPercentageCmd::Initialize() {
  SetTimeout(time);
}

// Called repeatedly when this Command is scheduled to run
void MoveIntakeArmPercentageCmd::Execute() {
  Robot::ballIntakeArm.moveArmSpeed(percentage);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveIntakeArmPercentageCmd::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void MoveIntakeArmPercentageCmd::End() {
  Robot::ballIntakeArm.stopArm();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveIntakeArmPercentageCmd::Interrupted() {
  End();
}
