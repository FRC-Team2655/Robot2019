#pragma once

#include <frc/commands/Command.h>

class IntakeHatchPanelAutoCommand : public frc::Command {
 public:
  IntakeHatchPanelAutoCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
