#pragma once

#include <frc/commands/Command.h>

class MoveIntakeArmTimeCommand : public frc::Command {
 public:
  MoveIntakeArmTimeCommand(double speed, double timeSec);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
  double speed, timeSec;
};
