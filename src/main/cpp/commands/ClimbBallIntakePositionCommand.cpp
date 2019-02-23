#include "commands/ClimbBallIntakePositionCommand.h"
#include <Robot.h>
#include <RobotMap.h>

ClimbBallIntakePositionCommand::ClimbBallIntakePositionCommand(double position) : position(position) {
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void ClimbBallIntakePositionCommand::Initialize() {
  // position / DOWN_DIRECTION is a sign (positive means moving in same direction aka down)
  // negative means moving in oppisate direction
  if(Robot::ballIntakeArm.isTopLimitSwitchPressed() && (position / BallIntakeDownDirection) < 0){
    // if at top and not trying to move down do not allow this action
    position = 0;
  }
}

// Called repeatedly when this Command is scheduled to run
void ClimbBallIntakePositionCommand::Execute() {
  if(Robot::hasEverResetBallIntakeArm)
    Robot::ballIntakeArm.armClimbPosition(position);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbBallIntakePositionCommand::IsFinished() { 
  return !Robot::hasEverResetBallIntakeArm;
}

// Called once after isFinished returns true
void ClimbBallIntakePositionCommand::End() {
  // DO NOT STOP THE ARM HERE!!! IT COULD CAUSE A JERK THAT WOULD MESS UP CLIMBING
  // WILL PROBABLY NEED TO HAND OFF TO A DIFFERENT PID (POSSIBLY DIFFERENT COMMAND)
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbBallIntakePositionCommand::Interrupted() {
  End();
}
