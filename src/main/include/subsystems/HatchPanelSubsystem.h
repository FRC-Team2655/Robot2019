#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>

class HatchPanelSubsystem : public frc::Subsystem {
 private:
  frc::DoubleSolenoid hatchPanal{0, 1, 2};
  frc::DoubleSolenoid hatchMover{0, 1, 2};
 public:
  HatchPanelSubsystem();
  void InitDefaultCommand() override;
  void OpenHatch();
  void CloseHatch();
  void ExtendHatch();
  void RetractHatch();
};