/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BallShooterSubsystem.h"

BallShooterSubsystem::BallShooterSubsystem() : Subsystem("BallShooterSubsystem") {}

void BallShooterSubsystem::InitDefaultCommand() {
 
}

void BallShooterSubsystem::MoveTalonSpeed(double speed){
    ballShooterMotor.Set(speed);
}

void BallShooterSubsystem::ExtendPiston(){
    ballShooterSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

void BallShooterSubsystem::RetractPiston(){
    ballShooterSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
}