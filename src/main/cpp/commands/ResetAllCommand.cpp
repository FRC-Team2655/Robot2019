#include "commands/ResetAllCommand.h"
#include <Robot.h>

ResetAllCommand::ResetAllCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  
}

// Called just before this Command runs the first time
void ResetAllCommand::Initialize() {
  Robot::ballIntakeArm.resetPosition();
  Robot::driveBase.resetIMU();
  Robot::driveBase.resetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void ResetAllCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ResetAllCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ResetAllCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetAllCommand::Interrupted() {}
 
 
