/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <commands/MoveIntakeArmCommand.h>
#include <Robot.h>

MoveIntakeArmCommand::MoveIntakeArmCommand(int position) : position(position) {
  Requires(&Robot::ballIntakeArm);
}

// Called just before this Command runs the first time
void MoveIntakeArmCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MoveIntakeArmCommand::Execute() {
  Robot::ballIntakeArm.movePosition(position);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveIntakeArmCommand::IsFinished() { 
  int currentPos = Robot::ballIntakeArm.getArmPosition();
  if(std::abs(currentPos - position) <= 10){
    return true;
  }
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
