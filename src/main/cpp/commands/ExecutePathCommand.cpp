#include <commands/ExecutePathCommand.h>
#include <RobotMap.h>
#include <iostream>

#define T_PER_REV 4096 // Pathfinder expects integer ticks. SPARK MAX uses doubles
// Need to convert to a "fraction" that pathfinder can work with

ExecutePathCommand::ExecutePathCommand() {
	Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void ExecutePathCommand::Initialize() {
	if (!startedFromAutoManager) {
		return;
	}

	// If there are not enough arguments, exit the function.
  if (arguments.size() < 2) {
    std::cout << "Not enough arguments" << std::endl;
    return;
  }

	// Load the paths from the roborio.
  FILE *leftFile = fopen(("/auto-paths/" + arguments[0] + "_left.csv").c_str(), "r");
	FILE *rightFile = fopen(("/auto-paths/" + arguments[0] + "_right.csv").c_str(), "r");

	// If the files do not exist, exit the function.
  if(!leftFile) {
    std::cout << "Left file not found" << std::endl;
    return;
  }
  if (!rightFile) {
    std::cout << "Right file not found" << std::endl;
    return;
  }

	// Parse CSVs (load trajectories from pathfinder CSV files.)
	leftLength = pathfinder_deserialize_csv(leftFile, leftTrajectory);
	rightLength = pathfinder_deserialize_csv(rightFile, rightTrajectory);

	fclose(leftFile);
	fclose(rightFile);

	double leftStartPos = Robot::driveBase.getLeftOutputPosition();
	double rightStartPos = Robot::driveBase.getRightOutputPosition();

	// initialEncoderPos, ticksPerRevolutions, WheelCircumference,
  //  kp, ki, kd, kv, ka
	leftConfig = {(int)(leftStartPos * T_PER_REV), T_PER_REV, WheelDiameter * 3.141592, 
					0.4, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0};
	rightConfig = {(int)(rightStartPos * T_PER_REV), T_PER_REV, WheelDiameter * 3.141592, 
					0.4, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0};
}

// Called repeatedly when this Command is scheduled to run
void ExecutePathCommand::Execute() {	
	// Get current power (as percentage) for L and R sides 
	//       based on current position and calculated trajectories
  double l = pathfinder_follow_encoder(leftConfig, &leftFollower, leftTrajectory, leftLength, 
									T_PER_REV * Robot::driveBase.getLeftOutputPosition());
	double r = pathfinder_follow_encoder(rightConfig, &rightFollower, rightTrajectory, rightLength, 
									T_PER_REV * Robot::driveBase.getRightOutputPosition());

	// Apply angle correction based on the IMU angle
	double gyro_heading = Robot::driveBase.getIMUAngle();
	double desired_heading = r2d(leftFollower.heading);
	double angle_difference = desired_heading - gyro_heading;
	double turn = 0.8 * (-1.0/80) * angle_difference;
	//l += turn;
	//r -= turn;

	Robot::driveBase.driveTankVelocity(l, r);
}

// Make this return true when this Command no longer needs to run execute()
bool ExecutePathCommand::IsFinished() { 
	return !startedFromAutoManager || false;
}

// Called once after isFinished returns true
void ExecutePathCommand::End() {
  	Robot::driveBase.driveTankVelocity(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExecutePathCommand::Interrupted() {
	End();
}
