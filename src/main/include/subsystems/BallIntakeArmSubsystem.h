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
  const double kpUp = 0.0005, kiUp = 0, kdUp = 1e-3, kfUp = 0, izoneUp = 0, minOutUp = -1, maxOutUp = 1;
  const double allowedErrorUp = 0, maxAccelUp = 2000, minVelocityUp = 0, maxVelocityUp = 4000;

  const double kpDown = 0.00075, kiDown = 1e-8, kdDown = 5e-4, kfDown = 0, izoneDown = 0, minOutDown = -1, maxOutDown = 1;
  const double allowedErrorDown = 0.01, maxAccelDown = 1000, minVelocityDown = 0, maxVelocityDown = 2000;

  const double kpClimb = 0.4, kiClimb = 0, kdClimb = 0, kfClimb = 0, izoneClimb = 0, minOutClimb = -1, maxOutClimb = 1;
  const double allowedErrorClimb = 0, maxAccelClimb = 18000, minVelocityClimb = 0, maxVelocityClimb = 6000;

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
