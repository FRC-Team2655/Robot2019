#pragma once

#include <frc/commands/Command.h>

class ResetAllCommand : public frc::Command {
 public:
  ResetAllCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
