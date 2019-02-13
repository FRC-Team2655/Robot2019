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
#include <frc/DigitalInput.h>

class BallIntakeArmSubsystem : public frc::Subsystem {
private:
  rev::CANSparkMax armMotor {IntakeArmMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANEncoder armEncoder = armMotor.GetEncoder();
  rev::CANPIDController armPid = armMotor.GetPIDController();
  frc::DigitalInput topLimitSwitch { 0 };

  const double gearRatio = (50.0 / 1.0) * (12.0 / 15.0);  // Gearbox ratio * sprocket ratio
  const double kp = 0.05, ki = 2.5e-5, kd = 1e-2, kf = 0, izone = 0, minOut = -0.5, maxOut = 0.5;
  const double allowedError = 0, maxAccel = 1000, minVelocity = 10, maxVelocity = 2000;

  //old configs: p=0.05, i=5e-5, d=1e-2, f=0

public:
  BallIntakeArmSubsystem();
  void InitDefaultCommand() override;
  void moveArmSpeed(double percentage);
  void moveToPosition(double ticks);
  void stopArm();
  double getArmPosition();
  void resetPosition();
  bool isTopLimitSwitchPressed();
};
