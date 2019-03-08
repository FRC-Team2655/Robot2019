#include "commands/PlaceHatchPanelAutoCommand.h"

PlaceHatchPanelAutoCommand::PlaceHatchPanelAutoCommand() {

}

// Called just before this Command runs the first time
void PlaceHatchPanelAutoCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PlaceHatchPanelAutoCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool PlaceHatchPanelAutoCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void PlaceHatchPanelAutoCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PlaceHatchPanelAutoCommand::Interrupted() {}
