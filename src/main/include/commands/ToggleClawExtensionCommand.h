#pragma once

#include <frc/commands/Command.h>

class ToggleClawExtensionCommand : public frc::Command {
 public:
  ToggleClawExtensionCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
