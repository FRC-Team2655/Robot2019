#pragma once

#include <frc/commands/Command.h>
#include <pathfinder.h>
#include <Robot.h>

#define BUFFER_LEN 1024

/**
 * Load csv files from the Roborio to drive the path. It must be executed from the auto manager.
 * Arguments:
 * 0 = path name
 * 1 = FRONT/BACK = Side of robot to follow path with
 * 2 = FORWARD/REVERSE = Order of path (ex. forward=pt1-pt4 reverse=pt4-pt1)
 * 3 = true/false starting angle zero
 */
class ExecutePathCommand : public team2655::AutoCommand {
public:
  ExecutePathCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

void adjustRelativeIMUAngle(double imuAngle, Segment *trajectory, size_t length);

private:

	bool startingAngleZero = false;
	bool hasEnded = false;

	double angleOffset = 0;

	// Make sure these are all upper case
	const std::string DRIVE_DIRECTION_FRONT = "FRONT";
	const std::string DRIVE_DIRECTION_BACK = "BACK";
	const std::string PATH_ORDER_FORWARD = "FORWARD";
	const std::string PATH_ORDER_REVERSE = "REVERSE";

	Segment leftTrajectory[BUFFER_LEN];
	Segment rightTrajectory[BUFFER_LEN];

	int leftLength;
	int rightLength;

	EncoderFollower leftFollower = {0, 0, 0, 0, 0};
	EncoderFollower rightFollower = {0, 0, 0, 0, 0};

	EncoderConfig leftConfig = {0, 0, 0, 0, 0, 0, 0, 0};
	EncoderConfig rightConfig = {0, 0, 0, 0, 0, 0, 0, 0};

	void reverseTrajectory(Segment *trajectory, int start, int end);
	void negatePositions(Segment *trajectory, size_t length);
	void flipHeading(Segment *trajectory, size_t length);

	int stopCounter = 0;
};
