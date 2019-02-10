/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveShooterWheelsCommand.h"

MoveShooterWheelsCommand::MoveShooterWheelsCommand(double percentage, bool intake) : percentage(std::abs(percentage)), intake(intake) {
  Requires(&Robot::ballShooter);
}

// Called just before this Command runs the first time
void MoveShooterWheelsCommand::Initialize() {
  if(intake)
    Robot::ballShooter.retractPiston();
}

// Called repeatedly when this Command is scheduled to run
void MoveShooterWheelsCommand::Execute() {
  if(intake)
    Robot::ballShooter.intake(percentage);
  else
    Robot::ballShooter.output(percentage);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveShooterWheelsCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void MoveShooterWheelsCommand::End() {
  Robot::ballShooter.moveSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveShooterWheelsCommand::Interrupted() {
  End();
}
