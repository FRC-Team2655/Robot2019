/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>
#include <RobotMap.h>

class LandingGearArmSubsystem : public frc::Subsystem {
private:
  rev::CANSparkMax landingGearArmMotor{LandingGearArmMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANEncoder landingGearArmEncoder = landingGearArmMotor.GetEncoder();
  rev::CANPIDController landingGearArmPid = landingGearArmMotor.GetPIDController();
  frc::Solenoid lockSolenoid {LockSolenoid};

  const double gearRatio = 40.0 / 1.0;
  const double kp = 0, ki = 0, kd = 0, kf = 0, izone = 0, minOut = -1, maxOut = 1;
  const double allowedError = 0, maxAccel = 0, minVelocity = 0, maxVelocity = 0;

public:
  LandingGearArmSubsystem();
  void InitDefaultCommand() override;
  void moveArmSpeed(double percentage);
  void moveArmPosition(double ticks);
  void stopArm();
  void lock();
  void unlock();
  double getArmPosition();
  void resetArmPosition();
  bool isLocked();
};
