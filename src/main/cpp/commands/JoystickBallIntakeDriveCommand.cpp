#include "commands/JoystickBallIntakeDriveCommand.h"
#include <Robot.h>

JoystickBallIntakeDriveCommand::JoystickBallIntakeDriveCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void JoystickBallIntakeDriveCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void JoystickBallIntakeDriveCommand::Execute() {
  double val = Robot::oi.js0->GetRawAxis(3);
  // PS4 Triggers are -1 by default
  if(val < 0)
    val = 0;

  if(val == 0){
    int pos = Robot::oi.js0->GetPOV();
    if((pos == 0 || pos == 45 || pos == 315) && !Robot::ballIntakeArm.isTopLimitSwitchPressed())
      Robot::ballIntakeArm.moveArmSpeed(BallIntakeDownDirection * -1 * 0.3);
    else
      Robot::ballIntakeArm.moveArmSpeed(0);
  }else{
      Robot::ballIntakeArm.moveArmSpeed(BallIntakeDownDirection * val);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickBallIntakeDriveCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void JoystickBallIntakeDriveCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickBallIntakeDriveCommand::Interrupted() {}
