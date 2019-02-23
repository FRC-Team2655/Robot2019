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


