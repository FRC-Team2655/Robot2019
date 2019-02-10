/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <subsystems/LandingGearArmSubsystem.h>
#include <iostream>
#include <frc/commands/Command.h>
#include <commands/LandingGearArmTimeCG.h>

LandingGearArmSubsystem::LandingGearArmSubsystem() : Subsystem("ExampleSubsystem") {
  landingGearArmMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  lockSolenoid.Set(false);

  resetArmPosition();

  // PID Settings
  landingGearArmPid.SetP(kp);
  landingGearArmPid.SetI(ki);
  landingGearArmPid.SetD(kd);
  landingGearArmPid.SetFF(kf);
  landingGearArmPid.SetIZone(izone);
  landingGearArmPid.SetOutputRange(minOut, maxOut);

  // Setup for Smart Motion
  landingGearArmPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal);
  landingGearArmPid.SetSmartMotionAllowedClosedLoopError(allowedError);
  landingGearArmPid.SetSmartMotionMaxAccel(maxAccel);
  landingGearArmPid.SetSmartMotionMaxVelocity(maxVelocity);
  landingGearArmPid.SetSmartMotionMinOutputVelocity(minVelocity);
}

void LandingGearArmSubsystem::moveArmSpeed(double percentage){
  if(!isLocked())
    landingGearArmMotor.Set(percentage);
}
void LandingGearArmSubsystem::moveArmPosition(double ticks){
  if(!isLocked())
    landingGearArmMotor.Set(ticks);
}
void LandingGearArmSubsystem::stopArm(){
  landingGearArmMotor.Set(0);
}
double LandingGearArmSubsystem::getArmPosition(){
  return landingGearArmEncoder.GetPosition();
}
void LandingGearArmSubsystem::resetArmPosition(){
  landingGearArmEncoder.SetPosition(0);
}

void LandingGearArmSubsystem::InitDefaultCommand() {
  
}

void LandingGearArmSubsystem::lock(){
  stopArm();
  lockSolenoid.Set(false);
}

void  LandingGearArmSubsystem::unlock(){
  lockSolenoid.Set(true);
  frc::Command *cmd = new LandingGearArmTimeCG(-0.1, .1);
  cmd->Start();
}

bool LandingGearArmSubsystem::isLocked(){
  return !lockSolenoid.Get();
}