/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveDistanceCommand.h"
#include <Robot.h>
#include <commands/ExecutePathCommand.h>

#define T_PER_REV 4096 // Pathfinder expects integer ticks. SPARK MAX uses doubles

DriveDistanceCommand::DriveDistanceCommand(double distance) : distance(distance / 39.37) {
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void DriveDistanceCommand::Initialize() {
  Waypoint pts[] = {{0, 0, 0}, {std::abs(distance), 0, 0}};
  candidate = new TrajectoryCandidate();
  pathfinder_prepare(pts, 2, 
        FIT_HERMITE_CUBIC, 
        PATHFINDER_SAMPLES_FAST, 
        0.02, PathfinderMaxVelocity, 10, 50, candidate);
  length = candidate->length;
  pathfinder_generate(candidate, baseTrajectory);
  pathfinder_modify_tank(baseTrajectory, length, leftTrajectory, rightTrajectory, 0.6223);

  if(distance < 0){
    // Drive with back of robot in reverse order
    ExecutePathCommand::reverseTrajectory(leftTrajectory, 0, length);
		ExecutePathCommand::reverseTrajectory(rightTrajectory, 0, length);
		ExecutePathCommand::negatePositions(rightTrajectory, length);
		ExecutePathCommand::negatePositions(leftTrajectory, length);
  }

  double leftStartPos = Robot::driveBase.getLeftOutputPosition();
	double rightStartPos = Robot::driveBase.getRightOutputPosition();

	// initialEncoderPos, ticksPerRevolutions, WheelCircumference,
  //  kp, ki, kd, kv, ka
	leftConfig = {(int)(leftStartPos * T_PER_REV), T_PER_REV, WheelDiameter * 3.141592, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0};
	rightConfig = {(int)(rightStartPos * T_PER_REV), T_PER_REV, WheelDiameter * 3.141592, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0};

  std::cout << "Initializing..." << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void DriveDistanceCommand::Execute() {
  double l = pathfinder_follow_encoder(leftConfig, &leftFollower, leftTrajectory, length, 
										T_PER_REV * Robot::driveBase.getLeftOutputPosition());
  double r = pathfinder_follow_encoder(rightConfig, &rightFollower, rightTrajectory, length, 
                  T_PER_REV * Robot::driveBase.getRightOutputPosition());

  Robot::driveBase.driveTankVelocity(l * MaxVelocity, r * MaxVelocity);

  std::cout << "Executing..." << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistanceCommand::IsFinished() { 
  if(std::abs(Robot::driveBase.getLeftVelocity()) < 1 && std::abs(Robot::driveBase.getRightVelocity() < 1))
		stopCounter++;
	else
		stopCounter = 0;

  return stopCounter >= 20;
}

// Called once after isFinished returns true
void DriveDistanceCommand::End() {
  std::cout << "Ending..." << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistanceCommand::Interrupted() {}
