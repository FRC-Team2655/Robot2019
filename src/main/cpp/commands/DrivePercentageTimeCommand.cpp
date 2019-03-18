/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DrivePercentageTimeCommand.h"
#include <Robot.h>
#include <RobotMap.h>

DrivePercentageTimeCommand::DrivePercentageTimeCommand(double percentage, double time) : time(time), percentage(percentage) {
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void DrivePercentageTimeCommand::Initialize() {
  SetTimeout(time);
}

// Called repeatedly when this Command is scheduled to run
void DrivePercentageTimeCommand::Execute() {
  Robot::driveBase.driveTankVelocity(MaxVelocity * percentage, MaxVelocity * percentage);
}

// Make this return true when this Command no longer needs to run execute()
bool DrivePercentageTimeCommand::IsFinished() { return IsTimedOut(); }

// Called once after isFinished returns true
void DrivePercentageTimeCommand::End() {
  Robot::driveBase.driveTankVelocity(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivePercentageTimeCommand::Interrupted() {
  End();
}
