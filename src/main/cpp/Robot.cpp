#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <team2655/autonomous.hpp>
#include <commands/DriveTimeCommand.h>
#include <commands/ExecutePathCommand.h>
#include <commands/MoveIntakeArmCommand.h>
#include <commands/ResetIntakeArmPosCG.h>

OI Robot::oi;
DriveBaseSubsystem Robot::driveBase;
BallIntakeArmSubsystem Robot::ballIntakeArm;
BallShooterSubsystem Robot::ballShooter;
HatchPanelClawSubsystem Robot::hatchPanelClaw;
LandingGearArmSubsystem Robot::landingGearArm;
LandingGearDriveSubsystem Robot::landingGearDrive;
bool Robot::hasEverResetBallIntakeArm = false;

void Robot::RobotInit() {
    // Register auto commands
    autoManager.registerCommand(team2655::CommandCreator<DriveTimeCommand>, false, "DRIVE");
    autoManager.registerCommand(team2655::CommandCreator<ExecutePathCommand>, false, "PATH");
}

void Robot::RobotPeriodic() {
    frc::SmartDashboard::PutNumber(LeftVelocity, driveBase.getLeftVelocity());
    frc::SmartDashboard::PutNumber(RightVelocity, driveBase.getRightVelocity());
    frc::SmartDashboard::PutNumber(ArmPosition, ballIntakeArm.getArmPosition());
    frc::SmartDashboard::PutNumber("Velcoity", ballShooter.getVelocity());
}

void Robot::DisabledInit() {
    ballIntakeArm.setBrakeMode();
}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::AutonomousInit() {
    ballIntakeArm.setCoastMode();
   // driveBase.setBrakeMode();

    /*autoManager.clearCommands();
    //autoManager.addCommand("DRIVE", {"0.25", "1"});
    autoManager.addCommandToScript("PATH", {"path"});
    autoCommandPtr = autoManager.getScriptCommand();
    autoCommandPtr.get()->Start();*/
}

void Robot::AutonomousPeriodic() { 
    frc::Scheduler::GetInstance()->Run(); 
    Robot::driveBase.driveTankVelocity(3000, 3000);
}


void Robot::TeleopInit() {
    driveBase.setCoastMode();
    ballIntakeArm.setCoastMode();
    ballShooter.retractPiston();
    hatchPanelClaw.retractClaw();
}

void Robot::TeleopPeriodic() {
    frc::Scheduler::GetInstance()->Run();
    bool isPressed = ballIntakeArm.isTopLimitSwitchPressed();
    if (isPressed && !wasPressed) {
        hasEverResetBallIntakeArm = true;
        frc::Command *cmd = new ResetIntakeArmPosCG();
        cmd->Start();
    }
    wasPressed = isPressed;
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
