/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

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
