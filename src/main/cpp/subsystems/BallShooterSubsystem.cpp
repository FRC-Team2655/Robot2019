/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BallShooterSubsystem.h"

#include <iostream>

BallShooterSubsystem::BallShooterSubsystem() : Subsystem("BallShooterSubsystem") {
    ballShooterMotor.SetNeutralMode(NeutralMode::Brake);

    ballShooterMotor.SetInverted(true);
}

void BallShooterSubsystem::InitDefaultCommand() {
 
}

void BallShooterSubsystem::moveSpeed(double speed){
    ballShooterMotor.Set(speed);
}

void BallShooterSubsystem::intake(double speed){
    retractPiston();
    ballShooterMotor.SetNeutralMode(NeutralMode::Brake);
    moveSpeed(std::abs(speed));
}

void BallShooterSubsystem::output(double speed){
    ballShooterMotor.SetNeutralMode(NeutralMode::Coast);
    moveSpeed(-std::abs(speed));
}

double BallShooterSubsystem::getVelocity(){
    return ballShooterMotor.GetSelectedSensorVelocity();
}

void BallShooterSubsystem::extendPiston(){
    ballShooterSolenoid.Set(BallShooter_Extend);
}

void BallShooterSubsystem::retractPiston(){
    ballShooterSolenoid.Set(BallShooter_Retract);
}

void BallShooterSubsystem::moveVelocity(double velocity) {
    ballShooterMotor.Set(ControlMode::Velocity, velocity);
}