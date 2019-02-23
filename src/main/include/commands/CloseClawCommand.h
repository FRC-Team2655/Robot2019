#pragma once

#include <frc/commands/Command.h>
#include <subsystems/HatchPanelClawSubsystem.h>
#include <Robot.h>

class CloseClawCommand : public frc::Command {
 public:
  CloseClawCommand(bool shouldClose);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  bool shouldClose;
};
