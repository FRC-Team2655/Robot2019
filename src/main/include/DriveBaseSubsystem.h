#pragma once

#include <frc/commands/Subsystem.h>

class DriveBaseSubsystem : public frc::Subsystem {
 private:

 public:
  DriveBaseSubsystem();
  void InitDefaultCommand() override;
  void drivePercentage(double speed, double rotation);
  void driveVelocity(double speed, double rotation);
  void driveTankVelocity(double lVel, double rVel);
  void driveTankPercentage(double leftPercentage, double rightPercentage);
  std::array<double, 2> arcadeDrive(double xSpeed, double zRotation);
  double getLeftPosition();
  double getRightPosition();
  double getLeftVelocity();
  double getRightVelocity();
  double getLeftOutputPosition();
  double getRightOutputPosition();
  double getLeftOutputVelocity();
  double getRightOutputVelocity();
  double getIMUAngle();
};
