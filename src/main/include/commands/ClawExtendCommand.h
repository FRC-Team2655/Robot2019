#pragma once

#include <frc/commands/Command.h>
#include <Robot.h>

class ClawExtendCommand : public team2655::AutoCommand {
public:
  ClawExtendCommand(bool shouldExtend = true);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  bool shouldExtend;
};
