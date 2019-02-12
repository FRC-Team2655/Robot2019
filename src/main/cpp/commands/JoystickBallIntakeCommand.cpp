#include "commands/JoystickBallIntakeCommand.h"

JoystickBallIntakeCommand::JoystickBallIntakeCommand() {
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void JoystickBallIntakeCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void JoystickBallIntakeCommand::Execute() {
  Robot::ballIntakeArm.moveArmSpeed(.75 * jshelper::getAxisValue(Robot::oi.ballIntakeAxisConfig, Robot::oi.js1->GetRawAxis(1)));
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickBallIntakeCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void JoystickBallIntakeCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickBallIntakeCommand::Interrupted() {
  End();
}
