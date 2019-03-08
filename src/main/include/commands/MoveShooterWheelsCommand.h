#pragma once

#include <frc/commands/Command.h>
#include <subsystems/BallShooterSubsystem.h>
#include <Robot.h>

class MoveShooterWheelsCommand : public frc::Command {
 public:
  MoveShooterWheelsCommand(double percentage, bool intake);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  double percentage;
  bool intake;
};
