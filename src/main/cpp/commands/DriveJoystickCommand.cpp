#include "commands/DriveJoystickCommand.h"
#include "Robot.h"

DriveJoystickCommand::DriveJoystickCommand() {
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void DriveJoystickCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveJoystickCommand::Execute() {
  double power = -1 * jshelper::getAxisValue(Robot::oi.driveAxisConfig, Robot::oi.js0->GetRawAxis(1));
	double rotate = .6 * jshelper::getAxisValue(Robot::oi.rotateAxisConfig, Robot::oi.js0->GetRawAxis(2));
	Robot::driveBase.driveVelocity(power, rotate);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveJoystickCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveJoystickCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveJoystickCommand::Interrupted() {}
