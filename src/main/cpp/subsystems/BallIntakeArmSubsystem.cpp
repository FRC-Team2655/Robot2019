#include <subsystems/BallIntakeArmSubsystem.h>
#include <commands/JoystickBallIntakeCommand.h>
#include <Robot.h>
#include <subsystems/BallIntakeArmSubsystem.h>

#include <iostream>

BallIntakeArmSubsystem::BallIntakeArmSubsystem() : Subsystem("BallIntakeArmSubsystem") {
  resetPosition();

  // Up PID Settings
  armPid.SetP(BallIntake_kpUp, BallIntake_UpPID);
  armPid.SetI(BallIntake_kiUp, BallIntake_UpPID);
  armPid.SetD(BallIntake_kdUp, BallIntake_UpPID);
  armPid.SetFF(BallIntake_kfUp, BallIntake_UpPID);
  armPid.SetIZone(BallIntake_izoneUp, BallIntake_UpPID);
  armPid.SetOutputRange(BallIntake_minOutUp, BallIntake_maxOutUp, BallIntake_UpPID);

  // Setup for Smart Motion
  armPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal, BallIntake_UpPID);
  armPid.SetSmartMotionAllowedClosedLoopError(BallIntake_allowedErrorUp, BallIntake_UpPID);
  armPid.SetSmartMotionMaxAccel(BallIntake_maxAccelUp, BallIntake_UpPID);
  armPid.SetSmartMotionMaxVelocity(BallIntake_maxVelocityUp, BallIntake_UpPID);
  armPid.SetSmartMotionMinOutputVelocity(BallIntake_minVelocityUp, BallIntake_UpPID);

  // Down PID Settings
  armPid.SetP(BallIntake_kpDown, BallIntake_DownPID);
  armPid.SetI(BallIntake_kiDown, BallIntake_DownPID);
  armPid.SetD(BallIntake_kdDown, BallIntake_DownPID);
  armPid.SetFF(BallIntake_kfDown, BallIntake_DownPID);
  armPid.SetIZone(BallIntake_izoneDown, BallIntake_DownPID);
  armPid.SetOutputRange(BallIntake_minOutDown, BallIntake_maxOutDown, BallIntake_DownPID);

  // Setup for Smart Motion
  armPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal, BallIntake_DownPID);
  armPid.SetSmartMotionAllowedClosedLoopError(BallIntake_allowedErrorDown, BallIntake_DownPID);
  armPid.SetSmartMotionMaxAccel(BallIntake_maxAccelDown, BallIntake_DownPID);
  armPid.SetSmartMotionMaxVelocity(BallIntake_maxVelocityDown, BallIntake_DownPID);
  armPid.SetSmartMotionMinOutputVelocity(BallIntake_minVelocityDown, BallIntake_DownPID);

   // Climb PID Settings
  armPid.SetP(BallIntake_kpClimb, BallIntake_ClimbPID);
  armPid.SetI(BallIntake_kiClimb, BallIntake_ClimbPID);
  armPid.SetD(BallIntake_kdClimb, BallIntake_ClimbPID);
  armPid.SetFF(BallIntake_kfClimb, BallIntake_ClimbPID);
  armPid.SetIZone(BallIntake_izoneClimb, BallIntake_ClimbPID);
  armPid.SetOutputRange(BallIntake_minOutClimb, BallIntake_maxOutClimb, BallIntake_ClimbPID);

  // Setup for Smart Motion
  armPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal, BallIntake_ClimbPID);
  armPid.SetSmartMotionAllowedClosedLoopError(BallIntake_allowedErrorClimb, BallIntake_ClimbPID);
  armPid.SetSmartMotionMaxAccel(BallIntake_maxAccelClimb, BallIntake_ClimbPID);
  armPid.SetSmartMotionMaxVelocity(BallIntake_maxVelocityClimb, BallIntake_ClimbPID);
  armPid.SetSmartMotionMinOutputVelocity(BallIntake_minVelocityClimb, BallIntake_ClimbPID);

  // Lock PID Settings
  armPid.SetP(BallIntake_kpLock, BallIntake_LockPID);
  armPid.SetI(BallIntake_kiLock, BallIntake_LockPID);
  armPid.SetD(BallIntake_kdLock, BallIntake_LockPID);
  armPid.SetFF(BallIntake_kfLock, BallIntake_LockPID);
  armPid.SetIZone(BallIntake_izoneLock, BallIntake_LockPID);
  armPid.SetOutputRange(BallIntake_minOutLock, BallIntake_maxOutLock, BallIntake_LockPID);

  // Setup for Smart Motion
  armPid.SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kTrapezoidal, BallIntake_LockPID);
  armPid.SetSmartMotionAllowedClosedLoopError(BallIntake_allowedErrorLock, BallIntake_LockPID);
  armPid.SetSmartMotionMaxAccel(BallIntake_maxAccelLock, BallIntake_LockPID);
  armPid.SetSmartMotionMaxVelocity(BallIntake_maxVelocityLock, BallIntake_LockPID);
  armPid.SetSmartMotionMinOutputVelocity(BallIntake_minVelocityLock, BallIntake_LockPID);

  armMotor.BurnFlash();
}

void BallIntakeArmSubsystem::moveArmSpeed(double percentage){
  /*if(Robot::hasEverResetBallIntakeArm){
    double pos = getArmPosition();
    double adjustedPos = restrictPosition(pos);
    if(pos != adjustedPos && std::abs(percentage) >= 0.1)
      percentage = 0.1;
  }*/
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
  //SetDefaultCommand(new JoystickBallIntakeCommand());
}

void BallIntakeArmSubsystem::lockPosition(){
  
  // Lock a little past 0
  double target = getArmPosition() + (0.0833333 * BallIntakeDownDirection * -1);
  armPid.SetReference(target, rev::ControlType::kPosition, BallIntake_LockPID);

}

void BallIntakeArmSubsystem::resetPosition() {
  armEncoder.SetPosition(0);
}

void BallIntakeArmSubsystem::moveToPosition(double revolutions){
  revolutions = restrictPosition(revolutions);
  if ((revolutions / BallIntakeDownDirection) <= 0) {
    // Moving up
    armPid.SetReference(revolutions * BallIntake_gearRatio, rev::ControlType::kPosition, BallIntake_UpPID);
  }else{
    // Moving Down
    armPid.SetReference(revolutions * BallIntake_gearRatio, rev::ControlType::kPosition, BallIntake_DownPID);
  }
}

void BallIntakeArmSubsystem::armClimbPosition(double position){
  armPid.SetReference(position * BallIntake_gearRatio, rev::ControlType::kSmartMotion, BallIntake_ClimbPID);
}

bool BallIntakeArmSubsystem::isTopLimitSwitchPressed(){
  return topLimitSwitch.Get() == BallIntake_LimitSwitchPressed;
}

void BallIntakeArmSubsystem::setCoastMode() {
  armMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}

void BallIntakeArmSubsystem::setBrakeMode() {
  armMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

double BallIntakeArmSubsystem::restrictPosition(double displacement) {
  if (BallIntakeDownDirection < 0) {
    // DownLimit is less than UpLimit
    if (displacement < -BallIntakeDownPosLimit){
      return -BallIntakeDownPosLimit;
    }
    if (displacement > BallIntakeUpPosLimit){
      return BallIntakeUpPosLimit;
    }
  }else{
    // DownLimit is greater than UpLimit
    if (displacement > BallIntakeDownPosLimit){
      return BallIntakeDownPosLimit;
    }
    if (displacement < -BallIntakeUpPosLimit){
      return -BallIntakeUpPosLimit;
    }
  }
  return displacement; 
}