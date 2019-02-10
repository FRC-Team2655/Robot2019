#include "subsystems/LandingGearDriveSubsystem.h"
#include <subsystems/DriveBaseSubsystem.h>

void LandingGearDriveSubsystem::InitDefaultCommand() {
}

LandingGearDriveSubsystem::LandingGearDriveSubsystem() : Subsystem("LandingGearDriveSubsystem") {
  landingGearMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

  resetPosition();

  // PID Settings
  landingGearPID.SetP(kp);
  landingGearPID.SetI(ki);
  landingGearPID.SetD(kd);
  landingGearPID.SetFF(kf);
  landingGearPID.SetIZone(izone);
  landingGearPID.SetOutputRange(minOut, maxOut);

  // Setup for Smart Motion
  landingGearPID.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal);
  landingGearPID.SetSmartMotionAllowedClosedLoopError(allowedError);
  landingGearPID.SetSmartMotionMaxAccel(maxAccel);
  landingGearPID.SetSmartMotionMaxVelocity(maxVelocity);
  landingGearPID.SetSmartMotionMinOutputVelocity(minVelocity);
}

void LandingGearDriveSubsystem::moveSpeed(double percentage){
  landingGearMotor.Set(percentage);
}

void LandingGearDriveSubsystem::stop(){
  landingGearMotor.Set(0);
}

double LandingGearDriveSubsystem::getPosition(){
  return landingGearEncoder.GetPosition();
}

void LandingGearDriveSubsystem::resetPosition() {
  landingGearEncoder.SetPosition(0);
}

void LandingGearDriveSubsystem::movePosition(double ticks){
  // For now use position will use smart motion
  landingGearPID.SetReference(ticks * gearRatio, rev::ControlType::kSmartMotion);
}
