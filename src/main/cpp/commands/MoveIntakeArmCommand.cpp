/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <commands/MoveIntakeArmCommand.h>
#include <Robot.h>

#define DOWN_DIRECTION -1

MoveIntakeArmCommand::MoveIntakeArmCommand(double position) : position(position) {
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void MoveIntakeArmCommand::Initialize() {
  // position / DOWN_DIRECTION is a sign (positive means moving in same direction aka down)
  // negative means moving in oppisate direction
  if(Robot::ballIntakeArm.isTopLimitSwitchPressed() && (position / DOWN_DIRECTION) < 0){
    // if at top and not trying to move down do not allow this action
    position = 0;
  }
}

// Called repeatedly when this Command is scheduled to run
void MoveIntakeArmCommand::Execute() {
  Robot::ballIntakeArm.moveToPosition(position);
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
