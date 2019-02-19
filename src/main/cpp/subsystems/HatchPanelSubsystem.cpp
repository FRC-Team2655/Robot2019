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
    clawSol.Set(Claw_Open);
}
void HatchPanelClawSubsystem::closeClaw(){
  clawSol.Set(Claw_Close);
}
void HatchPanelClawSubsystem::extendClaw(){
  extenderSol.Set(Claw_Extend);
}
void HatchPanelClawSubsystem::retractClaw(){
  closeClaw();
  extenderSol.Set(Claw_Retract);
}

bool HatchPanelClawSubsystem::isExtended(){
  return extenderSol.Get() == Claw_Extend;
}


