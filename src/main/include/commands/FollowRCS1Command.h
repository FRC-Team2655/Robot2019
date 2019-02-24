#pragma once

#include <frc/commands/Command.h>

class FollowRCS1Command : public frc::Command {
 public:
  FollowRCS1Command();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
