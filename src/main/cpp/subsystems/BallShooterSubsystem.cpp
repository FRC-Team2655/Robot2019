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

    ballShooterMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    ballShooterMotor.SetInverted(true);
    ballShooterMotor.Config_kP(0, 0, 0);
    ballShooterMotor.Config_kI(0, 0, 0);
    ballShooterMotor.Config_kD(0, 0, 0);
    ballShooterMotor.Config_kF(0, 0, 0);
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
    ballShooterSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

void BallShooterSubsystem::retractPiston(){
    ballShooterSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
}

void BallShooterSubsystem::moveVelocity(double velocity) {
    ballShooterMotor.Set(ControlMode::Velocity, velocity);
}