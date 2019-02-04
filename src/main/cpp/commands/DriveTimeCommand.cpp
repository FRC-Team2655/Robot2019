#include <commands/DriveTimeCommand.h>
#include <Robot.h>

DriveTimeCommand::DriveTimeCommand() {
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void DriveTimeCommand::Initialize() {
  if(startedFromAutoManager){
    if(arguments.size() < 2){
      Cancel();
      return;
    }
    speed = std::stod(arguments[0]);
    SetTimeout(std::stod(arguments[1]));
  }
}

// Called repeatedly when this Command is scheduled to run
void DriveTimeCommand::Execute() {
  Robot::driveBase.driveTankPercentage(speed, speed);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveTimeCommand::IsFinished() { 
  return !startedFromAutoManager || IsTimedOut(); 
}

// Called once after isFinished returns true
void DriveTimeCommand::End() {
  Robot::driveBase.driveTankPercentage(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveTimeCommand::Interrupted() {
  End(); //Stop doing what we are doing if another command takes priority
}
