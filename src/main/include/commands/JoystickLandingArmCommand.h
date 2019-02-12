#pragma once

#include <frc/commands/Command.h>
#include <Robot.h>
#include <OI.h>

class JoystickLandingArmCommand : public frc::Command {
 public:
  JoystickLandingArmCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
