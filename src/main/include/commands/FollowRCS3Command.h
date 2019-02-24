#pragma once

#include <frc/commands/Command.h>

class FollowRCS3Command : public frc::Command {
 public:
  FollowRCS3Command();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
