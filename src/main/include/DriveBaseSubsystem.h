#pragma once

#include <frc/commands/Subsystem.h>

class DriveBaseSubsystem : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  DriveBaseSubsystem();
  void InitDefaultCommand() override;
  void drivePercentage(double speed, double rotation);
  std::array<double, 2> arcadeDrive(double xSpeed, double zRotation);
};
