/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <RobotMap.h>
#include <rev/CANSparkMax.h>

class BallIntakeArmSubsystem : public frc::Subsystem {
private:
  rev::CANSparkMax armMotor {IntakeArmMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANEncoder armEncoder = armMotor.GetEncoder();
  rev::CANPIDController armPid = armMotor.GetPIDController();

  const double gearRatio = 50.0 / 1.0;  // Gearbox ratio * sprocket ratio
  const double kp = 0.0004, ki = 0.0000000001, kd = 0.0001, kf = 0, izone = 0, minOut = -1, maxOut = 1;
  const double allowedError = 0, maxAccel = 3500, minVelocity = 10, maxVelocity = 5500;

public:
  BallIntakeArmSubsystem();
  void InitDefaultCommand() override;
  void moveArmSpeed(double percentage);
  void moveToPosition(double ticks);
  void stopArm();
  double getArmPosition();
  void resetPosition();
};
