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
void MoveIntakeArmTimeCommand::Interrupted() {
  End();
}
