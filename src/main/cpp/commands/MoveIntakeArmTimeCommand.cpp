/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveIntakeArmTimeCommand.h"
#include <Robot.h>

MoveIntakeArmTimeCommand::MoveIntakeArmTimeCommand(double speed, double timeSec) : speed(speed),
                                                      timeSec(timeSec){
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void MoveIntakeArmTimeCommand::Initialize() {
  SetTimeout(timeSec);
}

// Called repeatedly when this Command is scheduled to run
void MoveIntakeArmTimeCommand::Execute() {
  Robot::ballIntakeArm.moveArmSpeed(speed);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveIntakeArmTimeCommand::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void MoveIntakeArmTimeCommand::End() {
  Robot::ballIntakeArm.stopArm();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveIntakeArmTimeCommand::Interrupted() {}
