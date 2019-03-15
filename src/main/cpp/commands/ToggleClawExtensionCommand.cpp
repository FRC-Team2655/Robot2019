#include "commands/ToggleClawExtensionCommand.h"
#include <Robot.h>
#include <commands/RetractClawCommandGroup.h>

ToggleClawExtensionCommand::ToggleClawExtensionCommand() {
  
}

// Called just before this Command runs the first time
void ToggleClawExtensionCommand::Initialize() {
  if(Robot::hatchPanelClaw.isExtended()){
    // Must use this to time unlock correctly
    frc::Command *cmd = new RetractClawCommandGroup();
    cmd->Start();
  }else{
    Robot::hatchPanelClaw.extendClaw();
  }
}

// Called repeatedly when this Command is scheduled to run
void ToggleClawExtensionCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ToggleClawExtensionCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ToggleClawExtensionCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleClawExtensionCommand::Interrupted() {}
