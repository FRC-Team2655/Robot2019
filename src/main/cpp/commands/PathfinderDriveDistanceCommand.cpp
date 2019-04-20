/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#define T_PER_REV 4096

#include "commands/PathfinderDriveDistanceCommand.h"

#include <pathfinder.h>
#include <Robot.h>

PathfinderDriveDistanceCommand::PathfinderDriveDistanceCommand(double inches) : inches(inches) {
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void PathfinderDriveDistanceCommand::Initialize() {
  if(startedFromAutoManager){
    if(arguments.size() < 1){
      std::cerr << "No distance given for pathfinder drive distance command!" << std::endl;
      End();
      return;
    }
    inches = std::stod(arguments[0]);
  }
  if(inches == 0){
    End();
    return;
  }
  const int pointCount = 2;
  Waypoint points[pointCount] = {
    {0, 0, d2r(Robot::driveBase.getIMUAngle())},
    {std::abs(inches), 0, d2r(Robot::driveBase.getIMUAngle())}
  };

  TrajectoryCandidate candidate;
  pathfinder_prepare(points, pointCount, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_FAST, 0.02, PathfinderMaxVelocity, 4.4531, 5.16196, &candidate);
  length = candidate.length;

  Segment *baseTrajectory = new Segment[length];
  pathfinder_generate(&candidate, baseTrajectory);

  leftTrajectory = new Segment[length];
  rightTrajectory = new Segment[length];

  pathfinder_modify_tank(baseTrajectory, length, leftTrajectory, rightTrajectory, 0.635);

  if(inches > 0)
    pfMode = PathfinderMode::FrontForward;
  else
    pfMode = PathfinderMode::BackForward;
  

  pathfindertools::trajetorySwapByMode(pfMode, &leftTrajectory, &rightTrajectory);

	double leftStartPos = Robot::driveBase.getLeftOutputPosition();
	double rightStartPos = Robot::driveBase.getRightOutputPosition();

	// initialEncoderPos, ticksPerRevolutions, WheelCircumference,
  	//  kp, ki, kd, kv, ka
	leftConfig = pathfindertools::createEncoderConfig((int)(leftStartPos * T_PER_REV), T_PER_REV, WheelDiameter * PI, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0, pfMode);
	rightConfig = pathfindertools::createEncoderConfig((int)(rightStartPos * T_PER_REV), T_PER_REV, WheelDiameter * PI, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0, pfMode);

	leftFollower = pathfindertools::createEncoderFollower(length, pfMode);
	rightFollower = pathfindertools::createEncoderFollower(length, pfMode);
}

// Called repeatedly when this Command is scheduled to run
void PathfinderDriveDistanceCommand::Execute() {
  if(!hasEnded){
    int lenc = Robot::driveBase.getLeftOutputPosition() * T_PER_REV;
		int renc = Robot::driveBase.getRightOutputPosition() * T_PER_REV;
		double l = pathfindertools::followEncoder(leftConfig, &leftFollower, leftTrajectory, length, lenc, pfMode);
		double r = pathfindertools::followEncoder(rightConfig, &rightFollower, rightTrajectory, length, renc, pfMode);

		// Apply angle correction based on the IMU angle
		double gyro_heading = Robot::driveBase.getIMUAngle();
		double desired_heading = r2d(leftFollower.heading);
		double angle_difference = desired_heading - gyro_heading;

		angle_difference = std::fmod(angle_difference, 360.0);

		if (std::abs(angle_difference) > 180.0) {
			angle_difference = (angle_difference > 0) ? angle_difference - 360 : angle_difference + 360;
		} 


		double turn = 0.6 * (-1.0/80) * angle_difference;

		l += turn;
		r -= turn;

		Robot::driveBase.driveTankVelocity(l * MaxVelocity, r * MaxVelocity);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool PathfinderDriveDistanceCommand::IsFinished() { 
  if(std::abs(Robot::driveBase.getLeftVelocity()) < 10 && std::abs(Robot::driveBase.getRightVelocity() < 10)){
		stopCounter++;
	}else{
		stopCounter = 0;
	}
	return hasEnded || stopCounter >= 20 || (leftFollower.finished && rightFollower.finished);  
}

// Called once after isFinished returns true
void PathfinderDriveDistanceCommand::End() {
  hasEnded = true;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PathfinderDriveDistanceCommand::Interrupted() {
  End();
}
