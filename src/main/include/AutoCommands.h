#pragma once

#include <Robot.h>
#include <team2655/autonomous.hpp>
#include <pathfinder.h>
 
class DriveCommand : public team2655::AutoCommand {
	void start(std::string commandname, std::vector<std::string> args) override;
	void process() override;
	void handleComplete() override;
private:
	double speed;
};

class PathCommand : public team2655::AutoCommand {
	void start(std::string commandname, std::vector<std::string> args) override;
	void process() override;
	void handleComplete() override;
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