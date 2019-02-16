/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchPanelClawSubsystem.h"

HatchPanelClawSubsystem::HatchPanelClawSubsystem() : Subsystem("HatchPanelClawSubsystem") {}

void HatchPanelClawSubsystem::InitDefaultCommand() {
}

void HatchPanelClawSubsystem::openClaw(){
  if(isExtended())
    clawSol.Set(frc::DoubleSolenoid::Value::kForward);
}
void HatchPanelClawSubsystem::closeClaw(){
  clawSol.Set(frc::DoubleSolenoid::Value::kReverse);
}
void HatchPanelClawSubsystem::extendClaw(){
  extenderSol.Set(frc::DoubleSolenoid::Value::kReverse);
}
void HatchPanelClawSubsystem::retractClaw(){
  closeClaw();
  extenderSol.Set(frc::DoubleSolenoid::Value::kForward);
}

bool HatchPanelClawSubsystem::isExtended(){
  return extenderSol.Get() == frc::DoubleSolenoid::Value::kReverse;
}


