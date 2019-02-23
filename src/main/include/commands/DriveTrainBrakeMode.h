#pragma once

#include <frc/commands/Command.h>

class DriveTrainBrakeMode : public frc::Command {
 public:
  DriveTrainBrakeMode(bool isBrake);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
  bool isBrake;
};
