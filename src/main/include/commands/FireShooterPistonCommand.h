#pragma once

#include <frc/commands/Command.h>
#include <subsystems/BallShooterSubsystem.h>
#include <Robot.h>

class FireShooterPistonCommand : public frc::Command {
public:
  FireShooterPistonCommand(bool shouldExtend);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  bool shouldExtend;
};
