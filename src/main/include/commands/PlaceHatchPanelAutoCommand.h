#pragma once

#include <frc/commands/Command.h>

class PlaceHatchPanelAutoCommand : public frc::Command {
 public:
  PlaceHatchPanelAutoCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
