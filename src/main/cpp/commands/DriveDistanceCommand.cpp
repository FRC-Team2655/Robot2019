/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveDistanceCommand.h"
#include <Robot.h>

DriveDistanceCommand::DriveDistanceCommand(double distance) : distance(distance) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void DriveDistanceCommand::Initialize() {
  avgStartPos = Robot::driveBase.getAvgOutputPos();
  if(startedFromAutoManager && arguments.size() >= 1){
    distance = std::stod(arguments[0]);
  }else{
    std::cerr << "Drive distance command not enough arguments" << std::endl;
  }

  endPos = avgStartPos + (distance / (6 * 3.1415926535));
}

// Called repeatedly when this Command is scheduled to run
void DriveDistanceCommand::Execute() {
  double sign = distance / std::abs(distance);
  Robot::driveBase.driveTankVelocity(sign * 0.2 * MaxVelocity, sign * 0.2 * MaxVelocity);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistanceCommand::IsFinished() {
  if(distance == 0 ) return true;
  else if(distance >= 0) return Robot::driveBase.getAvgOutputPos() >= endPos;
  else return Robot::driveBase.getAvgOutputPos() <= endPos;
}

// Called once after isFinished returns true
void DriveDistanceCommand::End() {
  Robot::driveBase.driveTankPercentage(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistanceCommand::Interrupted() {
  End();
}
