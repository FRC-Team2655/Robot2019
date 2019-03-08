#pragma once

#include <frc/commands/Command.h>

class AutoAlignCommand : public frc::Command {
 public:
  AutoAlignCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
