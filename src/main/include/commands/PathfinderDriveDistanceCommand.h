/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <team2655/autonomous.hpp>
#include <team2655/pftools.hpp>

using namespace team2655;

class PathfinderDriveDistanceCommand : public team2655::AutoCommand {
public:
  PathfinderDriveDistanceCommand(double inches = 0);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:

  Segment *leftTrajectory, *rightTrajectory;

  double inches;

  int stopCounter = 0;
  bool hasEnded = false;

  PathfinderMode pfMode;

	int length;

	EncoderFollower leftFollower = {0, 0, 0, 0, 0};
	EncoderFollower rightFollower = {0, 0, 0, 0, 0};

	EncoderConfig leftConfig = {0, 0, 0, 0, 0, 0, 0, 0};
	EncoderConfig rightConfig = {0, 0, 0, 0, 0, 0, 0, 0};
};
