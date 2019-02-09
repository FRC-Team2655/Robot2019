#include "subsystems/LandingGearDriveSubsystem.h"
#include <subsystems/DriveBaseSubsystem.h>

LandingGearDriveSubsystem::LandingGearDriveSubsystem() : Subsystem("ExampleSubsystem") {}

void LandingGearDriveSubsystem::InitDefaultCommand() {
}

LandingGearDriveSubsystem::LandingGearDriveSubsystem() : Subsystem("LandingGearDriveSubsystem") {
  landingGearMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  //resetPosition();

  // PID Settings
  landingGearPID.SetP(0.0004);
  landingGearPID.SetI(0.0000000001);
  landingGearPID.SetD(0.0001);
  landingGearPID.SetFF(0);
  landingGearPID.SetIZone(0);
  landingGearPID.SetOutputRange(-1, 1);

  // Setup for Smart Motion
  landingGearPID.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal);
  landingGearPID.SetSmartMotionAllowedClosedLoopError(IntakeArmAllowedError);
  landingGearPID.SetSmartMotionMaxAccel(IntakeArmMaxA);
  landingGearPID.SetSmartMotionMaxVelocity(IntakeArmMaxV);
  landingGearPID.SetSmartMotionMinOutputVelocity(IntakeArmMinV);
}

void LandingGearDriveSubsystem::moveLandingGearSpeed(double percentage){
  landingGearMotor.Set(percentage);
}

void LandingGearDriveSubsystem::stopLandingGear(){
  landingGearMotor.Set(0);
}

double LandingGearDriveSubsystem::getLandingGearPosition(){
  return landingGearEncoder.GetPosition();
}

void LandingGearDriveSubsystem::InitDefaultCommand() {
  
}

void LandingGearDriveSubsystem::resetLandingGearPosition() {
  landingGearEncoder.SetPosition(0);
}

void LandingGearDriveSubsystem::moveLandingGearToPosition(double ticks){
  // For now use position will use smart motion
  landingGearPID.SetReference(ticks * IntakeArmGearRatio, rev::ControlType::kSmartMotion);
}

void LandingGearDriveSubsystem::moveLandingGearSpeed(double speed){
  landingGearMotor.Set(speed);
}