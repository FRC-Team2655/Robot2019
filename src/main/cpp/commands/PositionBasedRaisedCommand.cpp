/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionBasedRaisedCommand.h"
#include <commands/MoveIntakeArmPercentageCmd.h>
#include <Robot.h>

PositionBasedRaisedCommand::PositionBasedRaisedCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void PositionBasedRaisedCommand::Initialize() {
  if(!Robot::ballIntakeArm.getAtRocketHeight()){
    (new MoveIntakeArmPercentageCmd(-1 * BallIntakeDownDirection * 0.4, 10))->Start();
  }else{
    (new MoveIntakeArmPercentageCmd(-1 * BallIntakeDownDirection * 0.3, 10))->Start();
  }
}

// Called repeatedly when this Command is scheduled to run
void PositionBasedRaisedCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool PositionBasedRaisedCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void PositionBasedRaisedCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionBasedRaisedCommand::Interrupted() {}
