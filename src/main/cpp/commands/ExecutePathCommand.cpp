#include <commands/ExecutePathCommand.h>
#include <RobotMap.h>
#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#define T_PER_REV 4096 // Pathfinder expects integer ticks. SPARK MAX uses doubles
// Need to convert to a "fraction" that pathfinder can work with

ExecutePathCommand::ExecutePathCommand() {
	Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void ExecutePathCommand::Initialize() {
	if (!startedFromAutoManager) {
		End();
		return;
	}

	Robot::driveBase.setRampRate(0);

	// If there are not enough arguments, exit the function.
  	if (arguments.size() < 3) {
    	std::cerr << "Not enough arguments" << std::endl;
    	End();
		return;
  	}

	// front = driving in the direction of the front of the robot
	// forward = following path in forward order (ex. pt1->pt2->pt3->pt4)
	bool front = true, forward = true;

	// Convert arguments to upper case
	std::transform(arguments[1].begin(), arguments[1].end(), arguments[1].begin(), ::toupper);
	std::transform(arguments[2].begin(), arguments[2].end(), arguments[2].begin(), ::toupper);

	// Parse drive direction
	if(arguments[1] == DRIVE_DIRECTION_FRONT) {
		front = true;
	} else if(arguments[1] == DRIVE_DIRECTION_BACK) {
		front = false;
	} else {
		std::cerr << "Unknown drive direction '" << arguments[1] << "'." << std::endl;
		End();
		return;
	}

	// Parse path order
	if(arguments[2] == PATH_ORDER_FORWARD) {
		forward = true;
	} else if(arguments[2] == PATH_ORDER_REVERSE) {
		forward = false;
	} else {
		std::cerr << "Unknown path order '" << arguments[2] << "'." << std::endl;
		End();
		return;
	}

	// Load the paths from the roborio.
	FILE *leftFile, *rightFile;

	leftFile = fopen(("/auto-paths/" + arguments[0] + "_left.csv").c_str(), "r");
	rightFile = fopen(("/auto-paths/" + arguments[0] + "_right.csv").c_str(), "r");

	// If the files do not exist, exit the function.
	if(!leftFile) {
		std::cerr << "Left file not found" << std::endl;
		End();
		return;
	}
	if (!rightFile) {
		std::cerr << "Right file not found" << std::endl;
		End();
		return;
	}

	// Parse CSVs (load trajectories from pathfinder CSV files.)
	int leftLength = pathfinder_deserialize_csv(leftFile, leftTrajectory);
	int rightLength = pathfinder_deserialize_csv(rightFile, rightTrajectory);

	length = std::min(leftLength, rightLength);

	fclose(leftFile);
	fclose(rightFile);

	if(front && forward)
		pfMode = PathfinderMode::FrontForward;
	else if(front && !forward)
		pfMode = PathfinderMode::FrontReverse;
	else if(!front && forward)
		pfMode = PathfinderMode::BackForward;
	else if(!front && !forward)
		pfMode = PathfinderMode::BackReverse; 

	pathfindertools::trajetorySwapByMode(pfMode, &leftTrajectory, &rightTrajectory);

	double leftStartPos = Robot::driveBase.getLeftOutputPosition();
	double rightStartPos = Robot::driveBase.getRightOutputPosition();

	// initialEncoderPos, ticksPerRevolutions, WheelCircumference,
  	//  kp, ki, kd, kv, ka
	leftConfig = pathfindertools::createEncoderConfig((int)(leftStartPos * T_PER_REV), T_PER_REV, WheelDiameter * PI, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0, pfMode);
	rightConfig = pathfindertools::createEncoderConfig((int)(rightStartPos * T_PER_REV), T_PER_REV, WheelDiameter * PI, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0, pfMode);

	leftFollower = pathfindertools::createEncoderFollower(leftLength, pfMode);
	rightFollower = pathfindertools::createEncoderFollower(rightLength, pfMode);
}

// Called repeatedly when this Command is scheduled to run
void ExecutePathCommand::Execute() {
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


		double turn = 0.8 * (-1.0/80) * angle_difference;

		l += turn;
		r -= turn;

		Robot::driveBase.driveTankVelocity(l * MaxVelocity, r * MaxVelocity);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ExecutePathCommand::IsFinished() { 
	if(std::abs(Robot::driveBase.getLeftVelocity()) < 10 && std::abs(Robot::driveBase.getRightVelocity() < 10)){
		stopCounter++;
	}else{
		stopCounter = 0;
	}
	return !startedFromAutoManager || hasEnded || stopCounter >= 20 || (leftFollower.finished && rightFollower.finished);
}

// Called once after isFinished returns true
void ExecutePathCommand::End() {
	hasEnded = true;
  	Robot::driveBase.driveTankVelocity(0.0, 0.0);
	Robot::driveBase.setRampRate(DriveRampRate);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExecutePathCommand::Interrupted() {
	End();
}

void ExecutePathCommand::reverseTrajectory(Segment *trajectory, int start, int end) {
  while (start < end) { 
        Segment temp = trajectory[start];
        trajectory[start] = trajectory[end]; 
        trajectory[end] = temp; 
        start++; 
        end--; 
  }  
}

void ExecutePathCommand::negatePositions(Segment *trajectory, size_t length){
	for (size_t i = 0; i < length; ++i){
		trajectory[i].position *= -1;
		trajectory[i].velocity *= -1;
		trajectory[i].acceleration *= -1;
		trajectory[i].jerk *= -1;
		trajectory[i].x *= -1;
		trajectory[i].y *= -1;
	}
}