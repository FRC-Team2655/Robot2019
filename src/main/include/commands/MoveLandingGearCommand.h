/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <subsystems/LandingGearDriveSubsystem.h>
#include <subsystems/LandingGearArmSubsystem.h>

class MoveLandingGearCommand : public frc::Command {
public:
  MoveLandingGearCommand(double position, bool positionMode);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  double value;
  bool positionMode;
};
