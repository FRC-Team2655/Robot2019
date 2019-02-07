/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BallIntakeArmSubsystem.h"

BallIntakeArmSubsystem::BallIntakeArmSubsystem() : Subsystem("BallIntakeArmSubsystem") {
  armMotor.ConfigNominalOutputForward(0);
  armMotor.ConfigNominalOutputReverse(0);
  armMotor.ConfigPeakOutputForward(0.5);
  armMotor.ConfigPeakOutputReverse(-0.5);

  armMotor.Config_kF(0, 0.0);
	armMotor.Config_kP(0, 0.1);
	armMotor.Config_kI(0, 0.0);
  armMotor.Config_kD(0, 0.0);
}

void BallIntakeArmSubsystem::stopArm(){
  armMotor.Set(0);
}

int BallIntakeArmSubsystem::getArmPosition(){
  return armMotor.GetSelectedSensorPosition();
}

void BallIntakeArmSubsystem::InitDefaultCommand() {
  
}

void BallIntakeArmSubsystem::movePosition(double ticks){
  armMotor.Set(ControlMode::Position, ticks * IntakeArmGearRatio);
}


