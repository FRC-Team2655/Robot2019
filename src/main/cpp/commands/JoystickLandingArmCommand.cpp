#include "commands/JoystickLandingArmCommand.h"

JoystickLandingArmCommand::JoystickLandingArmCommand() {
  Requires(&Robot::landingGearArm);
}

// Called just before this Command runs the first time
void JoystickLandingArmCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void JoystickLandingArmCommand::Execute() {
  /*double armVal = Robot::oi.js1->GetRawAxis(5);
  if(armVal > 0.2)
    armVal = 0.2;
  Robot::landingGearArm.moveArmSpeed(-.8 * jshelper::getAxisValue(Robot::oi.landingGearAxisConfig, armVal));

  double val = Robot::oi.js1->GetRawAxis(3);
  if(val < 0)
    val = 0;
  Robot::landingGearDrive.moveSpeed(-0.5 * jshelper::getAxisValue(Robot::oi.landingGearAxisConfig, val));*/
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickLandingArmCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void JoystickLandingArmCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickLandingArmCommand::Interrupted() {
  End();
}
