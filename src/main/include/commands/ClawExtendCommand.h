#pragma once

#include <frc/commands/Command.h>
#include <Robot.h>

class ClawExtendCommand : public frc::Command {
public:
  ClawExtendCommand(bool shouldExtend);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  bool shouldExtend;
};
