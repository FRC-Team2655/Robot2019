#pragma once

#include <frc/commands/Command.h>

class StopIntakeArmCommand : public frc::Command {
 public:
  StopIntakeArmCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
