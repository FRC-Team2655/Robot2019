#pragma once

#include <frc/commands/Command.h>

class ClimbBallIntakePositionCommand : public frc::Command {
public:
  ClimbBallIntakePositionCommand(double position);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  double position;
};
