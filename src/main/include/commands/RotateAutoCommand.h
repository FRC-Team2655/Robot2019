#pragma once

#include <frc/commands/Command.h>

#include <team2655/autonomous.hpp>

/**
 * Rotates the robot to a desired heading
 * Arguments (1):
 * Heading
 */
class RotateAutoCommand : public team2655::AutoCommand {
public:
  RotateAutoCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
