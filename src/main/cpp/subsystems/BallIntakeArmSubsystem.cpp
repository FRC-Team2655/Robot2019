/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#define UpPID 0
#define DownPID 1
#define ClimbPID 2

#include <subsystems/BallIntakeArmSubsystem.h>
#include <commands/JoystickBallIntakeCommand.h>
#include <Robot.h>
#include <subsystems/BallIntakeArmSubsystem.h>

#include <iostream>

BallIntakeArmSubsystem::BallIntakeArmSubsystem() : Subsystem("BallIntakeArmSubsystem") {
  setBrakeMode();

  resetPosition();

  // Up PID Settings
  armPid.SetP(kpUp, UpPID);
  armPid.SetI(kiUp, UpPID);
  armPid.SetD(kdUp, UpPID);
  armPid.SetFF(kfUp, UpPID);
  armPid.SetIZone(izoneUp, UpPID);
  armPid.SetOutputRange(minOutUp, maxOutUp, UpPID);

  // Setup for Smart Motion
  armPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal, UpPID);
  armPid.SetSmartMotionAllowedClosedLoopError(allowedErrorUp, UpPID);
  armPid.SetSmartMotionMaxAccel(maxAccelUp, UpPID);
  armPid.SetSmartMotionMaxVelocity(maxVelocityUp, UpPID);
  armPid.SetSmartMotionMinOutputVelocity(minVelocityUp, UpPID);

  // Down PID Settings
  armPid.SetP(kpDown, DownPID);
  armPid.SetI(kiDown, DownPID);
  armPid.SetD(kdDown, DownPID);
  armPid.SetFF(kfDown, DownPID);
  armPid.SetIZone(izoneDown, DownPID);
  armPid.SetOutputRange(minOutDown, maxOutDown, DownPID);

  // Setup for Smart Motion
  armPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal, DownPID);
  armPid.SetSmartMotionAllowedClosedLoopError(allowedErrorDown, DownPID);
  armPid.SetSmartMotionMaxAccel(maxAccelDown, DownPID);
  armPid.SetSmartMotionMaxVelocity(maxVelocityDown, DownPID);
  armPid.SetSmartMotionMinOutputVelocity(minVelocityDown, DownPID);

   // Climb PID Settings
  armPid.SetP(kpClimb, ClimbPID);
  armPid.SetI(kiClimb, ClimbPID);
  armPid.SetD(kdClimb, ClimbPID);
  armPid.SetFF(kfClimb, ClimbPID);
  armPid.SetIZone(izoneClimb, ClimbPID);
  armPid.SetOutputRange(minOutClimb, maxOutClimb, ClimbPID);

  // Setup for Smart Motion
  armPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal, ClimbPID);
  armPid.SetSmartMotionAllowedClosedLoopError(allowedErrorClimb, ClimbPID);
  armPid.SetSmartMotionMaxAccel(maxAccelClimb, ClimbPID);
  armPid.SetSmartMotionMaxVelocity(maxVelocityClimb, ClimbPID);
  armPid.SetSmartMotionMinOutputVelocity(minVelocityClimb, ClimbPID);
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

double BallIntakeArmSubsystem::getArmVelocity(){
  return armEncoder.GetVelocity();
}

void BallIntakeArmSubsystem::InitDefaultCommand() {
  SetDefaultCommand(new JoystickBallIntakeCommand());
}

void BallIntakeArmSubsystem::resetPosition() {
  armEncoder.SetPosition(0);
}

void BallIntakeArmSubsystem::moveToPosition(double revolutions){
  if ((revolutions / BallIntakeDownDirection) <= 0) {
    // Moving up
    armPid.SetReference(revolutions * gearRatio, rev::ControlType::kSmartMotion, UpPID);
  }else{
    // Moving Down
    armPid.SetReference(revolutions * gearRatio, rev::ControlType::kSmartMotion, DownPID);
  }
}

void BallIntakeArmSubsystem::armClimbPosition(double position){
  armPid.SetReference(position * gearRatio, rev::ControlType::kPosition, ClimbPID);
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