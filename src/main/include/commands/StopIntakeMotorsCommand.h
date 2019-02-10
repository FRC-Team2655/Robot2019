#pragma once

#include <frc/commands/Command.h>
#include <Robot.h>

class StopIntakeMotorsCommand : public frc::Command {
 public:
  StopIntakeMotorsCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
