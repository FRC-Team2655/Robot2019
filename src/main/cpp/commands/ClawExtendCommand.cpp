#include "commands/ClawExtendCommand.h"
#include <Robot.h>

ClawExtendCommand::ClawExtendCommand(bool shouldExtend) : shouldExtend(shouldExtend) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ClawExtendCommand::Initialize() {
    if(startedFromAutoManager){
      std::transform(commandName.begin(), commandName.end(), commandName.begin(), ::tolower);
      if(commandName == "extend_claw"){
        shouldExtend = true;
      }else if(commandName == "retract_claw"){
        shouldExtend = false;
      }else{
        return;
      }
    }
    if (shouldExtend) {
      Robot::hatchPanelClaw.extendClaw();
    }else {
      Robot::hatchPanelClaw.retractClaw();
    }
}

// Called repeatedly when this Command is scheduled to run
void ClawExtendCommand::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool ClawExtendCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ClawExtendCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClawExtendCommand::Interrupted() {}
