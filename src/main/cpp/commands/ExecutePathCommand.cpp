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
		End();
		return;
	}

	std::cout << "Running path: " << arguments[0] << std::endl;

	// If there are not enough arguments, exit the function.
  	if (arguments.size() < 4) {
    	std::cerr << "Not enough arguments" << std::endl;
    	End();
		return;
  	}

	// front = driving in the direction of the front of the robot
	// forward = following path in forward order (ex. pt1->pt2->pt3->pt4)
	bool front, forward;
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

	std::transform(arguments[3].begin(), arguments[3].end(), arguments[3].begin(), ::tolower);
	if(arguments[3] == "true"){
		startingAngleZero = true;
		angleOffset = Robot::driveBase.getIMUAngle();
	}else if(arguments[3] == "false"){
		startingAngleZero = false;
	}else{
		std::cerr << "Execute path command unknown argument #4." << std::endl;
		End();
		return;
	}

	// Load the paths from the roborio.
	FILE *leftFile, *rightFile;

	// If driving in forward order with back of robot or reverse order with the front or the robot
	//            left and right trajectories need to be swapped
	if((!front && forward) || (front && !forward)){
		// switched left and right paths 
		rightFile = fopen(("/auto-paths/" + arguments[0] + "_left.csv").c_str(), "r");
		leftFile = fopen(("/auto-paths/" + arguments[0] + "_right.csv").c_str(), "r");
	}else{
		leftFile = fopen(("/auto-paths/" + arguments[0] + "_left.csv").c_str(), "r");
		rightFile = fopen(("/auto-paths/" + arguments[0] + "_right.csv").c_str(), "r");
	}

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
	leftLength = pathfinder_deserialize_csv(leftFile, leftTrajectory);
	rightLength = pathfinder_deserialize_csv(rightFile, rightTrajectory);

	fclose(leftFile);
	fclose(rightFile);

	// If driving with the back of the robot in forward order flip the headings and negate positions
	if (!front && forward){
		flipHeading(leftTrajectory, leftLength);
		flipHeading(rightTrajectory, rightLength);
		negatePositions(leftTrajectory,leftLength);
		negatePositions(rightTrajectory, rightLength);
	}

	// If 
	if (!front && !forward){
		reverseTrajectory(leftTrajectory, 0, leftLength);
		reverseTrajectory(rightTrajectory, 0, rightLength);
		negatePositions(rightTrajectory, rightLength);
		negatePositions(leftTrajectory, leftLength);
	}

	if (front && !forward){
		flipHeading(leftTrajectory, leftLength);
		flipHeading(rightTrajectory, rightLength);
		reverseTrajectory(leftTrajectory, 0, leftLength);
		reverseTrajectory(rightTrajectory, 0, rightLength);
	}

	double leftStartPos = Robot::driveBase.getLeftOutputPosition();
	double rightStartPos = Robot::driveBase.getRightOutputPosition();

	// initialEncoderPos, ticksPerRevolutions, WheelCircumference,
  	//  kp, ki, kd, kv, ka
	leftConfig = {(int)(leftStartPos * T_PER_REV), T_PER_REV, WheelDiameter * 3.141592, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0};
	rightConfig = {(int)(rightStartPos * T_PER_REV), T_PER_REV, WheelDiameter * 3.141592, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0};
}

// Called repeatedly when this Command is scheduled to run
void ExecutePathCommand::Execute() {
	if(!hasEnded){	
		// Get current power (as percentage) for L and R sides 
		//       based on current position and calculated trajectories
		double l = pathfinder_follow_encoder(leftConfig, &leftFollower, leftTrajectory, leftLength, 
										T_PER_REV * Robot::driveBase.getLeftOutputPosition());
		double r = pathfinder_follow_encoder(rightConfig, &rightFollower, rightTrajectory, rightLength, 
										T_PER_REV * Robot::driveBase.getRightOutputPosition());

		// Apply angle correction based on the IMU angle
		double gyro_heading = Robot::driveBase.getIMUAngle() - angleOffset;
		double desired_heading = r2d(leftFollower.heading);
		double angle_difference = desired_heading - gyro_heading;
		double turn = 0.8 * (-1.0/80) * angle_difference;

		//std::cout << "GyroAngle: " << gyro_heading << std::endl;
		//std::cout << "DesiredHeading: " << desired_heading << std::endl;
		//std::cout << "AngleDifference: " << angle_difference << std::endl;

		//l += turn;
		//r -= turn;

		Robot::driveBase.driveTankVelocity(l * MaxVelocity, r * MaxVelocity);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ExecutePathCommand::IsFinished() { 
	if(std::abs(Robot::driveBase.getLeftVelocity()) < 1 && std::abs(Robot::driveBase.getRightVelocity() < 1))
		stopCounter++;
	else
		stopCounter = 0;

	return !startedFromAutoManager || hasEnded || stopCounter >= 20;
}

// Called once after isFinished returns true
void ExecutePathCommand::End() {
	hasEnded = true;
  	Robot::driveBase.driveTankVelocity(0.0, 0.0);
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

void ExecutePathCommand::flipHeading(Segment *trajectory, size_t length){
	for (size_t i = 0; i < length; ++i){
		trajectory[i].heading += PI;
	}
}