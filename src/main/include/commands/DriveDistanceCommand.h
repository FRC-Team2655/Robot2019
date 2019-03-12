#pragma once

#include <frc/commands/Command.h>

#include <pathfinder.h>


class DriveDistanceCommand : public frc::Command {
public:
  DriveDistanceCommand(double distance);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  double distance;
  int stopCounter = 0;
  TrajectoryCandidate *candidate;
  Segment *baseTrajectory = new Segment[1024],
          *leftTrajectory = new Segment[1024],
          *rightTrajectory = new Segment[1024];
  int length;

  EncoderConfig leftConfig, rightConfig;
  EncoderFollower leftFollower, rightFollower;
};
