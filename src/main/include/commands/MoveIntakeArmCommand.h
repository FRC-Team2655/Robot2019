#pragma once

#include <frc/commands/Command.h>

class MoveIntakeArmCommand : public frc::Command {
public:
  MoveIntakeArmCommand(double position);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  double position;
};
