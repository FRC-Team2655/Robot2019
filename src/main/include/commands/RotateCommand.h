/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <team2655/autonomous.hpp>

class RotateCommand : public team2655::AutoCommand {
 public:
  RotateCommand(double heading = 0);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
  double heading;
  int stopCounter = 0;
  int headingChangeCounter = 0;
  double lastHeading = 0;
};
