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
  leftStartPos = Robot::driveBase.getLeftOutputPosition();
  rightStartPos = Robot::driveBase.getRightOutputPosition();

  desired_heading = Robot::driveBase.getIMUAngle();
  if(startedFromAutoManager && arguments.size() >= 1){
    distance = std::stod(arguments[0]);
  }else{
    std::cerr << "Drive distance command not enough arguments" << std::endl;
  }

  endPos = distance / (6 * 3.1415926535);
}

// Called repeatedly when this Command is scheduled to run
void DriveDistanceCommand::Execute() {
	double gyro_heading = Robot::driveBase.getIMUAngle();
	double angle_difference = desired_heading - gyro_heading;

	angle_difference = std::fmod(angle_difference, 360.0);
	if (std::abs(angle_difference) > 180.0) {
		angle_difference = (angle_difference > 0) ? angle_difference - 360 : angle_difference + 360;
	} 

	double turn = 0.8 * (-1.0/80) * angle_difference;

  //double l = sign * speed;
  //double r = sign * speed;
  double leftDistanceTraveled = Robot::driveBase.getLeftOutputPosition() - leftStartPos;
  double rightDistanceTraveled = Robot::driveBase.getRightOutputPosition() - rightStartPos;
  double distanceTraveled = (leftDistanceTraveled + rightDistanceTraveled) / 2.0;
  double distanceLeft = endPos - distanceTraveled;
  const double rampupThreshold = 2.0;
  const double rampdownThreshold = 6.0;

  // [distance from start or end] / threshold + minSpeed
  double rampup = std::abs(endPos - distanceLeft) / rampupThreshold + 0.3;
  double rampdown = std::abs(distanceLeft) / rampdownThreshold + 0.1;
  
  double speed = std::copysign(MINVAL(1.0, MINVAL(rampup, rampdown)) , distanceLeft);

  Robot::driveBase.driveTankVelocity((speed + turn) * MaxVelocity, (speed - turn) * MaxVelocity);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistanceCommand::IsFinished() {
  double leftDistanceTraveled = Robot::driveBase.getLeftOutputPosition() - leftStartPos;
  double rightDistanceTraveled = Robot::driveBase.getRightOutputPosition() - rightStartPos;
  double distanceTraveled = (leftDistanceTraveled + rightDistanceTraveled) / 2.0;

  if (distance == 0) {
    return true;
  }

  if (Robot::driveBase.getLeftVelocity() < 10 && Robot::driveBase.getRightVelocity() < 10) {
    stopCounter++;
  }else{
    stopCounter = 0;
  }

   if (distanceTraveled >= endPos || stopCounter >= 10) {
    return true;
  } 
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
