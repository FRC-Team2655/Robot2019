#include "commands/FollowRCS1Command.h"

FollowRCS1Command::FollowRCS1Command() {

}

// Called just before this Command runs the first time
void FollowRCS1Command::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FollowRCS1Command::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool FollowRCS1Command::IsFinished() { return false; }

// Called once after isFinished returns true
void FollowRCS1Command::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowRCS1Command::Interrupted() {}
