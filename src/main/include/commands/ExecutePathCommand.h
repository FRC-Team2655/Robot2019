#pragma once

#include <frc/commands/Command.h>
#include <pathfinder.h>
#include <Robot.h>
#include <team2655/autonomous.hpp>

#define BUFFER_LEN 1024

/**
 * Load csv files from the Roborio to drive the path. It must be executed from the auto manager.
 * Arguments:
 * 0 = path name
 * 1 = FRONT/BACK = Side of robot to follow path with
 * 2 = FORWARD/REVERSE = Order of path (ex. forward=pt1-pt4 reverse=pt4-pt1)
 */
class ExecutePathCommand : public team2655::AutoCommand {
public:
  ExecutePathCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

  static void reverseTrajectory(Segment *trajectory, int start, int end);
  static void negatePositions(Segment *trajectory, size_t length);
  static void flipHeading(Segment *trajectory, size_t length);


private:

	bool headingCorrection = true;
	bool hasEnded = false;

	// Make sure these are all upper case
	const std::string DRIVE_DIRECTION_FRONT = "FRONT";
	const std::string DRIVE_DIRECTION_BACK = "BACK";
	const std::string PATH_ORDER_FORWARD = "FORWARD";
	const std::string PATH_ORDER_REVERSE = "REVERSE";

	Segment leftTrajectory[BUFFER_LEN];
	Segment rightTrajectory[BUFFER_LEN];

	bool front, forward;

	int leftLength;
	int rightLength;

	EncoderFollower leftFollower = {0, 0, 0, 0, 0};
	EncoderFollower rightFollower = {0, 0, 0, 0, 0};

	EncoderConfig leftConfig = {0, 0, 0, 0, 0, 0, 0, 0};
	EncoderConfig rightConfig = {0, 0, 0, 0, 0, 0, 0, 0};

	int stopCounter = 0;
};
