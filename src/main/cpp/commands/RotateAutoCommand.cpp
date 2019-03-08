#include "commands/RotateAutoCommand.h"
#include <Robot.h>

RotateAutoCommand::RotateAutoCommand() {
    Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void RotateAutoCommand::Initialize() {
    if(startedFromAutoManager && arguments.size() >= 1){
        SetTimeout(5);
        double heading = std::stod(arguments[0]);
        Robot::driveBase.rotateToHeading(heading);
    }else{
        Cancel();
    }
}

// Called repeatedly when this Command is scheduled to run
void RotateAutoCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool RotateAutoCommand::IsFinished() { return !startedFromAutoManager || IsTimedOut() || false; }

// Called once after isFinished returns true
void RotateAutoCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateAutoCommand::Interrupted() {
    End();
}
