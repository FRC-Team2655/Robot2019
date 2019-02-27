#pragma once

#include <frc/commands/Command.h>
#include <pathfinder.h>
#include <Robot.h>

#define BUFFER_LEN 1024

/**
 * Load csv files from the Roborio to drive the path. It must be executed from the auto manager.
 * Arguments:
 * 0 = path name
 */
class ExecutePathCommand : public team2655::AutoCommand {
public:
  ExecutePathCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
	Segment leftTrajectory[BUFFER_LEN];
	Segment rightTrajectory[BUFFER_LEN];

	int leftLength;
	int rightLength;

	EncoderFollower leftFollower = {0, 0, 0, 0, 0};
	EncoderFollower rightFollower = {0, 0, 0, 0, 0};

	EncoderConfig leftConfig = {0, 0, 0, 0, 0, 0, 0, 0};
	EncoderConfig rightConfig = {0, 0, 0, 0, 0, 0, 0, 0};

	void reverseTrajectory(Segment *trajectory, int start, int end);
};
