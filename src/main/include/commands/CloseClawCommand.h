#pragma once

#include <frc/commands/Command.h>
#include <subsystems/HatchPanelClawSubsystem.h>
#include <Robot.h>
#include <team2655/autonomous.hpp>

class CloseClawCommand : public team2655::AutoCommand {
 public:
  CloseClawCommand(bool shouldClose = false);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  bool shouldClose;
};
