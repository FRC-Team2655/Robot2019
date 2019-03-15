#include "commands/CloseClawCommand.h"
#include <Robot.h>

CloseClawCommand::CloseClawCommand(bool shouldClose) : shouldClose(shouldClose) {

  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CloseClawCommand::Initialize() {

  std::transform(commandName.begin(), commandName.end(), commandName.begin(), ::toupper);

  if (startedFromAutoManager && commandName == "CLOSE_CLAW") {
    shouldClose = true;
  }else if (startedFromAutoManager && commandName == "OPEN_CLAW") {
    shouldClose = false;
  }

  if (shouldClose) {
    Robot::hatchPanelClaw.closeClaw();
  }else{
    Robot::hatchPanelClaw.openClaw();
  }
}

// Called repeatedly when this Command is scheduled to run
void CloseClawCommand::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool CloseClawCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void CloseClawCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CloseClawCommand::Interrupted() {}
