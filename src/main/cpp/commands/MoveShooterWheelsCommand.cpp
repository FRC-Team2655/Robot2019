#include "commands/MoveShooterWheelsCommand.h"
#include <Robot.h>

MoveShooterWheelsCommand::MoveShooterWheelsCommand(double percentage, bool intake) : percentage(std::abs(percentage)), intake(intake) {
  Requires(&Robot::ballShooter);
}

// Called just before this Command runs the first time
void MoveShooterWheelsCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void MoveShooterWheelsCommand::Execute() {
  if(intake)
    Robot::ballShooter.intake(percentage);
  else
    Robot::ballShooter.output(percentage);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveShooterWheelsCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void MoveShooterWheelsCommand::End() {
  Robot::ballShooter.moveSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveShooterWheelsCommand::Interrupted() {
  End();
}
