#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <team2655/autonomous.hpp>
#include <commands/DriveTimeCommand.h>

OI Robot::oi;
DriveBaseSubsystem Robot::driveBase;

void Robot::RobotInit() {
    // Register auto commands
    autoManager.registerCommand(team2655::CommandCreator<DriveTimeCommand>, false, "DRIVE");
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::AutonomousInit() {
    driveBase.setBrakeMode();

    autoManager.clearCommands();
    autoManager.addCommand("DRIVE", {"0.25", "1"});
    autoCommandPtr = autoManager.getScriptCommand();
    std::cout << "Cmd count: " << autoCommandPtr.get()->GetSize() << std::endl;
    /*team2655::AutoCommand *cmd = new DriveTimeCommand();
    cmd->startedFromAutoManager = true;
    cmd->commandName = "DRIVE";
    cmd->arguments = {"0.1", "1"};
    cmd->Start();*/
}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit() {
    driveBase.setCoastMode();
}

void Robot::TeleopPeriodic() { 
    frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
