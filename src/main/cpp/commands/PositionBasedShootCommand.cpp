/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionBasedShootCommand.h"
#include <Robot.h>

PositionBasedShootCommand::PositionBasedShootCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::ballShooter);
}

// Called just before this Command runs the first time
void PositionBasedShootCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PositionBasedShootCommand::Execute() {
  if(Robot::ballIntakeArm.getAtRocketHeight()){
    Robot::ballShooter.output(0.3);
  }else{
    Robot::ballShooter.output(1);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool PositionBasedShootCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void PositionBasedShootCommand::End() {
  Robot::ballShooter.output(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionBasedShootCommand::Interrupted() {
  End();
}
