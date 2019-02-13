/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <subsystems/BallIntakeArmSubsystem.h>
#include <commands/JoystickBallIntakeCommand.h>
#include <Robot.h>

#include <iostream>

BallIntakeArmSubsystem::BallIntakeArmSubsystem() : Subsystem("BallIntakeArmSubsystem") {
  setBrakeMode();

  resetPosition();

  // PID Settings
  armPid.SetP(kp);
  armPid.SetI(ki);
  armPid.SetD(kd);
  armPid.SetFF(kf);
  armPid.SetIZone(izone);
  armPid.SetOutputRange(minOut, maxOut);

  // Setup for Smart Motion
  armPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal);
  armPid.SetSmartMotionAllowedClosedLoopError(allowedError);
  armPid.SetSmartMotionMaxAccel(maxAccel);
  armPid.SetSmartMotionMaxVelocity(maxVelocity);
  armPid.SetSmartMotionMinOutputVelocity(minVelocity);
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
  SetDefaultCommand(new JoystickBallIntakeCommand());
}

void BallIntakeArmSubsystem::resetPosition() {
  armEncoder.SetPosition(0);
}

void BallIntakeArmSubsystem::moveToPosition(double revolutions){
  // For now use position will use smart motion
  armPid.SetReference(revolutions * gearRatio, rev::ControlType::kPosition);
}

bool BallIntakeArmSubsystem::isTopLimitSwitchPressed(){
  return !topLimitSwitch.Get();
}

void BallIntakeArmSubsystem::setCoastMode() {
  armMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}

void BallIntakeArmSubsystem::setBrakeMode() {
  armMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}