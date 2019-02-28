#include <commands/MoveIntakeArmCommand.h>
#include <Robot.h>
#include <RobotMap.h>

MoveIntakeArmCommand::MoveIntakeArmCommand(double position) : position(position) {
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void MoveIntakeArmCommand::Initialize() {
  // position / DOWN_DIRECTION is a sign (positive means moving in same direction aka down)
  // negative means moving in oppisate direction
  if(Robot::ballIntakeArm.isTopLimitSwitchPressed() && (position / BallIntakeDownDirection) < 0){
    // if at top and not trying to move down do not allow this action
    position = BallIntakeUpPos;
  }
}

// Called repeatedly when this Command is scheduled to run
void MoveIntakeArmCommand::Execute() {
  if(Robot::hasEverResetBallIntakeArm){
    Robot::ballIntakeArm.moveToPosition(position);
  }else if ((position / BallIntakeDownDirection) <= 0){
    Robot::ballIntakeArm.moveArmSpeed(-1 * 0.3 * BallIntakeDownDirection);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool MoveIntakeArmCommand::IsFinished() { 
  return false;
}

// Called once after isFinished returns true
void MoveIntakeArmCommand::End() {
  Robot::ballIntakeArm.stopArm();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveIntakeArmCommand::Interrupted() {
  End();
}
