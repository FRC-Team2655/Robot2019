/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveDistanceCommand.h"
#include <Robot.h>
#include <team2655/pftools.hpp>

DriveDistanceCommand::DriveDistanceCommand(double distance) : distance(distance) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void DriveDistanceCommand::Initialize() {
  desired_heading = Robot::driveBase.getIMUAngle();
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

  double speed = 0.2;
  double sign = distance / std::abs(distance);

	double gyro_heading = Robot::driveBase.getIMUAngle();
	double angle_difference = desired_heading - gyro_heading;

	angle_difference = std::fmod(angle_difference, 360.0);
	if (std::abs(angle_difference) > 180.0) {
		angle_difference = (angle_difference > 0) ? angle_difference - 360 : angle_difference + 360;
	} 

	double turn = 0.8 * (-1.0/80) * angle_difference;

  double l = sign * speed;
  double r = sign * speed;

	l += turn;
	r -= turn;

  Robot::driveBase.driveTankVelocity(l * MaxVelocity, r * MaxVelocity);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistanceCommand::IsFinished() {
  if(std::abs(Robot::driveBase.getLeftVelocity()) < 10 && std::abs(Robot::driveBase.getRightVelocity() < 10)){
		stopCounter++;
	}else{
		stopCounter = 0;
	}

  if(distance == 0 || stopCounter >= 20) return true;
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
