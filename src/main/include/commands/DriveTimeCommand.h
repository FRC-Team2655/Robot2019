#pragma once

#include <frc/commands/Command.h>
#include <team2655/autonomous.hpp>

/**
 * Drive a command based off of a given time and speed. It must be executed from the auto manager.
 */
class DriveTimeCommand : public team2655::AutoCommand {
public:
  DriveTimeCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  
private: 
  double speed;
};
