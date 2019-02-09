/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchPanelSubsystem.h"

HatchPanelSubsystem::HatchPanelSubsystem() : Subsystem("ExampleSubsystem") {}

void HatchPanelSubsystem::InitDefaultCommand() {
}

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>

void InitDefaultCommand(){

}
void HatchPanelSubsystem::OpenHatch(){
  hatchPanal.Set(frc::DoubleSolenoid::Value::kForward);
}
void HatchPanelSubsystem::CloseHatch(){
  hatchPanal.Set(frc::DoubleSolenoid::Value::kReverse);
}
void HatchPanelSubsystem::ExtendHatch(){
  hatchMover.Set(frc::DoubleSolenoid::Value::kForward);
}
void HatchPanelSubsystem::RetractHatch(){
  hatchMover.Set(frc::DoubleSolenoid::Value::kReverse);
}



