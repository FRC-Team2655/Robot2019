/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <subsystems/BallIntakeArmSubsystem.h>

#include <iostream>

BallIntakeArmSubsystem::BallIntakeArmSubsystem() : Subsystem("BallIntakeArmSubsystem") {
  armMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  resetPosition();

  // PID Settings
  armPid.SetP(0.0004);
  armPid.SetI(0.0000000001);
  armPid.SetD(0.0001);
  armPid.SetFF(0);
  armPid.SetIZone(0);
  armPid.SetOutputRange(-1, 1);

  // Setup for Smart Motion
  armPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal);
  armPid.SetSmartMotionAllowedClosedLoopError(IntakeArmAllowedError);
  armPid.SetSmartMotionMaxAccel(IntakeArmMaxA);
  armPid.SetSmartMotionMaxVelocity(IntakeArmMaxV);
  armPid.SetSmartMotionMinOutputVelocity(IntakeArmMinV);
}

void BallIntakeArmSubsystem::moveArmSpeed(double percentage){
  armMotor.Set(percentage);
}

void BallIntakeArmSubsystem::stopArm(){
  armMotor.Set(0);
}

double BallIntakeArmSubsystem::getArmPosition(){
  return armEncoder.GetPosition();
}

void BallIntakeArmSubsystem::InitDefaultCommand() {
  
}

void BallIntakeArmSubsystem::resetPosition() {
  armEncoder.SetPosition(0);
}

void BallIntakeArmSubsystem::moveToPosition(double revolutions){
  // For now use position will use smart motion
  armPid.SetReference(revolutions * IntakeArmGearRatio, rev::ControlType::kSmartMotion);
}


