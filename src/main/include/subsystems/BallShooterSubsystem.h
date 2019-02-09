#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <RobotMap.h>
#include <frc/DoubleSolenoid.h>

class BallShooterSubsystem : public frc::Subsystem {
 private:
  WPI_TalonSRX ballShooterMotor{BallShooter};
  frc::DoubleSolenoid ballShooterSolenoid{0,1,2};
 public:
  BallShooterSubsystem();
  void InitDefaultCommand() override;
};
