/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/WPILib.h>
#include <RobotMap.h>

class BallIntakeArmSubsystem : public frc::Subsystem {
private:
  WPI_TalonSRX armMotor { IntakeArmMotor };
public:
  BallIntakeArmSubsystem();
  void InitDefaultCommand() override;
  void movePosition(double ticks);
  void stopArm();
  int getArmPosition();
};
