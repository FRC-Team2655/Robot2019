#pragma once

#include <frc/commands/Command.h>
#include <Robot.h>
#include <OI.h>

class JoystickBallIntakeCommand : public frc::Command {
 public:
  JoystickBallIntakeCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
