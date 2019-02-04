#pragma once

#include <frc/commands/Command.h>

/**
 * Drive the driveBase with input from the joysticks
 */
class DriveJoystickCommand : public frc::Command {
public:
  DriveJoystickCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
