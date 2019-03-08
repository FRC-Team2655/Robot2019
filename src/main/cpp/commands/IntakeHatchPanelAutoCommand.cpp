#include "commands/IntakeHatchPanelAutoCommand.h"

IntakeHatchPanelAutoCommand::IntakeHatchPanelAutoCommand() {

}

// Called just before this Command runs the first time
void IntakeHatchPanelAutoCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeHatchPanelAutoCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool IntakeHatchPanelAutoCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void IntakeHatchPanelAutoCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeHatchPanelAutoCommand::Interrupted() {}
