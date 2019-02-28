#include "subsystems/HatchPanelClawSubsystem.h"

#include <commands/LockClawTimeCG.h>

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
  frc::Command *cmd = new LockClawTimeCG(0.4);
  cmd->Start();
}
void HatchPanelClawSubsystem::retractClaw(){
  unlock();
  closeClaw();
  extenderSol.Set(Claw_Retract);
}

bool HatchPanelClawSubsystem::isExtended(){
  return extenderSol.Get() == Claw_Extend;
}

void HatchPanelClawSubsystem::lock(){
  lockSolenoid.Set(Claw_Lock);
}

void HatchPanelClawSubsystem::unlock(){
  lockSolenoid.Set(Claw_Unlock);
}
