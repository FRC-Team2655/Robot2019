#include "commands/ResetIntakeArmEncoderCommand.h"
#include <Robot.h>

ResetIntakeArmEncoderCommand::ResetIntakeArmEncoderCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ResetIntakeArmEncoderCommand::Initialize() {
  Robot::ballIntakeArm.resetPosition();
}

// Called repeatedly when this Command is scheduled to run
void ResetIntakeArmEncoderCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ResetIntakeArmEncoderCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ResetIntakeArmEncoderCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetIntakeArmEncoderCommand::Interrupted() {}
