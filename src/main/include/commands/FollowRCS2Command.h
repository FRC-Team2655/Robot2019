#pragma once

#include <frc/commands/Command.h>

class FollowRCS2Command : public frc::Command {
 public:
  FollowRCS2Command();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
