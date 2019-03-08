#pragma once

#include <frc/commands/Command.h>

class JoystickBallIntakeDriveCommand : public frc::Command {
 public:
  JoystickBallIntakeDriveCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
