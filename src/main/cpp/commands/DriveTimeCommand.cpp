#include <commands/DriveTimeCommand.h>
#include <Robot.h>

DriveTimeCommand::DriveTimeCommand() {
  Requires(&Robot::driveBase);
}

// Called just before this Command runs the first time
void DriveTimeCommand::Initialize() {
  // If there are not enough arguments, then do not run autonomous.
  if(startedFromAutoManager){
    if(arguments.size() < 2){
      Cancel();
      return;
    }

    // Getting the speed from the first argument and converting it to a double.
    speed = std::stod(arguments[0]);

    // Starting the time using the second argument.
    SetTimeout(std::stod(arguments[1]));
  }
}

// Called repeatedly when this Command is scheduled to run
void DriveTimeCommand::Execute() {
  // Drive the robot using the speed.
  Robot::driveBase.driveTankPercentage(speed, speed);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveTimeCommand::IsFinished() { 
  // If the time we set using the second argument is done, stop driving.
  return !startedFromAutoManager || IsTimedOut(); 
}

// Called once after isFinished returns true
void DriveTimeCommand::End() {
  // Set the speeds for both sides to 0 to stop driving the robot.
  Robot::driveBase.driveTankPercentage(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveTimeCommand::Interrupted() {
  End(); //Stop doing what we are doing if another command takes priority
}
