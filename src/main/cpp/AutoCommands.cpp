#include <AutoCommands.h>
#include <Robot.h>
#include <pathfinder.h>

#include <string>

void DriveCommand::start(std::string commandname, std::vector<std::string> args) {
	if (arguments.size() < 2) {
		complete();
		return;
	}
	std::cout << arguments[1] << " seconds" << std::endl;
	std::cout << arguments[0] << "power" << std::endl;
	setTimeout((int)(std::stod(arguments[1])*1000));
	speed = std::stod(arguments[0]);
}

void DriveCommand::process() {
	Robot::currentRobot->driveBase.drivePercentage(speed, 0);
	std::cout << "Process is running" << std::endl;
	
}

void DriveCommand::handleComplete() {
	Robot::currentRobot->driveBase.drivePercentage(0, 0);
	std::cout << "Completed" << std::endl;
}

void PathCommand::start(std::string commandname, std::vector<std::string> args) {
	FILE *leftFile = fopen(("/auto-paths/" + args[0] + "_left.csv").c_str(), "r");
	FILE *rightFile = fopen(("/auto-paths/" + args[0] + "_right.csv").c_str(), "r");

	leftLength = pathfinder_deserialize_csv(leftFile, leftTrajectory);
	rightLength = pathfinder_deserialize_csv(rightFile, rightTrajectory);

	fclose(leftFile);
	fclose(rightFile);

	double leftStartPos = Robot::currentRobot->driveBase.getLeftOutputPosition();
	double rightStartPos = Robot::currentRobot->driveBase.getRightOutputPosition();

	leftConfig = {leftStartPos, 1, WheelDiameter * 3.141592, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0};
	rightConfig = {rightStartPos, 1, WheelDiameter * 3.141592, 
					1.0, 0.0, 0.0, 1.0 / PathfinderMaxVelocity, 0.0};
}

void PathCommand::process() {
	double l = pathfinder_follow_encoder(leftConfig, &leftFollower, leftTrajectory, leftLength, 
										Robot::currentRobot->driveBase.getLeftOutputPosition());
	double r = pathfinder_follow_encoder(rightConfig, &rightFollower, rightTrajectory, rightLength, 
										Robot::currentRobot->driveBase.getRightOutputPosition());

	double gyro_heading = Robot::currentRobot->driveBase.getIMUAngle();
	double desired_heading = r2d(leftFollower.heading);
	double angle_difference = desired_heading - gyro_heading;
	double turn = 0.8 * (-1.0/80) * angle_difference;

	l += turn;
	r -= turn;

	Robot::currentRobot->driveBase.driveTankVelocity(l * MaxVelocity, r * MaxVelocity);
}

void PathCommand::handleComplete() {
	Robot::currentRobot->driveBase.driveTankVelocity(0, 0);
}