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
