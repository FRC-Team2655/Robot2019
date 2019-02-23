#pragma once

#include <frc/commands/Command.h>

class ResetIntakeArmEncoderCommand : public frc::Command {
 public:
  ResetIntakeArmEncoderCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
