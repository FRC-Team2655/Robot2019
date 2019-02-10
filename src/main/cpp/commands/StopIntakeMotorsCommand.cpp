
#include "commands/StopIntakeMotorsCommand.h"

StopIntakeMotorsCommand::StopIntakeMotorsCommand() {
  Requires(&Robot::ballShooter);
}

// Called just before this Command runs the first time
void StopIntakeMotorsCommand::Initialize() {
  Robot::ballShooter.moveSpeed(0);
}

// Called repeatedly when this Command is scheduled to run
void StopIntakeMotorsCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool StopIntakeMotorsCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void StopIntakeMotorsCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopIntakeMotorsCommand::Interrupted() {
  End();
}
