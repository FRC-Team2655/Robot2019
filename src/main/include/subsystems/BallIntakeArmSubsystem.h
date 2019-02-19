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
  frc::DigitalInput topLimitSwitch { LimitSwitchID };

public:
  BallIntakeArmSubsystem();
  void InitDefaultCommand() override;
  void moveArmSpeed(double percentage);
  void moveToPosition(double ticks);

  /**
   * ONLY USE WHEN CLIMBING!!! TOO AGRESSIVE FOR NORMAL USE. FOR NORMAL USE USE moveToPosition
   * Move the ball intake arm to a sepecified position at a high velocity for climbing
   */
  void armClimbPosition(double position);

  void stopArm();
  double getArmPosition();
  double getArmVelocity();
  void resetPosition();
  bool isTopLimitSwitchPressed();
  void setCoastMode();
  void setBrakeMode();
};
