#pragma once

#include <frc/commands/Command.h>
#include <pathfinder.h>
#include <Robot.h>

/**
 * Load csv files from the Roborio to drive the path. It must be executed from the auto manager.
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
	Segment leftTrajectory[1024];
	Segment rightTrajectory[1024];

	int leftLength;
	int rightLength;

	EncoderFollower leftFollower = {0, 0, 0, 0, 0};
	EncoderFollower rightFollower = {0, 0, 0, 0, 0};

	EncoderConfig leftConfig = {0, 0, 0, 0, 0, 0, 0, 0};
	EncoderConfig rightConfig = {0, 0, 0, 0, 0, 0, 0, 0};
};
