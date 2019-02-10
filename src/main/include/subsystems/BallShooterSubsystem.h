#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <RobotMap.h>
#include <frc/DoubleSolenoid.h>

class BallShooterSubsystem : public frc::Subsystem {
public:
  BallShooterSubsystem();
  void moveSpeed(double speed);
  void intake(double speed);
  void output(double speed);
  void extendPiston();
  void retractPiston();
  void InitDefaultCommand() override;

private:
  WPI_TalonSRX ballShooterMotor{BallShooter};
  frc::DoubleSolenoid ballShooterSolenoid { ShooterSolenoidA, ShooterSolenoidB };
};
