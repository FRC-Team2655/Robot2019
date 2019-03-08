#pragma once

#include <frc/commands/Command.h>

class MoveIntakeArmPercentageCommand : public frc::Command {
 public:
  MoveIntakeArmPercentageCommand(double speed);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
  double speed;
};
