#include "commands/FollowRCS2Command.h"

FollowRCS2Command::FollowRCS2Command() {

}

// Called just before this Command runs the first time
void FollowRCS2Command::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FollowRCS2Command::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool FollowRCS2Command::IsFinished() { return false; }

// Called once after isFinished returns true
void FollowRCS2Command::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowRCS2Command::Interrupted() {}
