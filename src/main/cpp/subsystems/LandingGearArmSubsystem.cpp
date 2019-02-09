/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <subsystems/LandingGearArmSubsystem.h>

LandingGearArmSubsystem::LandingGearArmSubsystem() : Subsystem("ExampleSubsystem") {
  landingGearArmMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  //resetPosition();

  // PID Settings
  landingGearArmPid.SetP(0.0);
  landingGearArmPid.SetI(0.0);
  landingGearArmPid.SetD(0.0);
  landingGearArmPid.SetFF(0);
  landingGearArmPid.SetIZone(0);
  landingGearArmPid.SetOutputRange(-1, 1);

  // Setup for Smart Motion
  /*landingGearArmPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal);
  landingGearArmPid.SetSmartMotionAllowedClosedLoopError();
  landingGearArmPid.SetSmartMotionMaxAccel();
  landingGearArmPid.SetSmartMotionMaxVelocity();
  landingGearArmPid.SetSmartMotionMinOutputVelocity();*/
}

void LandingGearArmSubsystem::moveLandingArmSpeed(double percentage){
  landingGearArmMotor.Set(percentage);
}
void LandingGearArmSubsystem::moveLandingArmToPosition(double ticks){
  landingGearArmMotor.Set(ticks);
}
void LandingGearArmSubsystem::stopLandingArm(){
  landingGearArmMotor.Set(0);
}
double LandingGearArmSubsystem::getLandingArmPosition(){
  return landingGearArmEncoder.GetPosition();
}
void LandingGearArmSubsystem::resetLandingArmPosition(){
  landingGearArmEncoder.SetPosition(0);
}

void LandingGearArmSubsystem::InitDefaultCommand() {
  
}