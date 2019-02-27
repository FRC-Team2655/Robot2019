#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <team2655/autonomous.hpp>
#include <commands/DriveTimeCommand.h>
#include <commands/ExecutePathCommand.h>
#include <commands/MoveIntakeArmCommand.h>
#include <commands/ResetIntakeArmPosCG.h>
#include <commands/ClimbCommandGroup.h>

OI Robot::oi;
DriveBaseSubsystem Robot::driveBase;
BallIntakeArmSubsystem Robot::ballIntakeArm;
BallShooterSubsystem Robot::ballShooter;
HatchPanelClawSubsystem Robot::hatchPanelClaw;
bool Robot::hasEverResetBallIntakeArm = false;

void Robot::RobotInit() {
    // Register auto commands
    autoManager.registerCommand(team2655::CommandCreator<ExecutePathCommand>, false, "PATH");
    std::cout << PathfinderMaxVelocity << std::endl;
}

void Robot::RobotPeriodic() {
    frc::SmartDashboard::PutNumber(LeftVelocity, driveBase.getLeftVelocity());
    frc::SmartDashboard::PutNumber(RightVelocity, driveBase.getRightVelocity());
    frc::SmartDashboard::PutNumber(ArmPosition, ballIntakeArm.getArmPosition());
    frc::SmartDashboard::PutBoolean("LimitSwitchPressed", ballIntakeArm.isTopLimitSwitchPressed());
    frc::SmartDashboard::PutNumber("Intake Arm Vecolity: ", ballIntakeArm.getArmVelocity());
    frc::SmartDashboard::PutNumber("IMU Angle: ", driveBase.getIMUAngle());
}

void Robot::DisabledInit() {
    ballIntakeArm.setBrakeMode();
}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::AutonomousInit() {
    DefaultSolonoidState();

    ballIntakeArm.setCoastMode();
    driveBase.setBrakeMode();

    autoManager.clearCommands();
    autoManager.addCommandToScript("PATH", {"TestPath"});
    autoCommandPtr = autoManager.getScriptCommand();
    autoCommandPtr.get()->Start();
}

void Robot::AutonomousPeriodic() { 
    LimitSwitchReset();
    frc::Scheduler::GetInstance()->Run(); 
}


void Robot::TeleopInit() {
    DefaultSolonoidState();
    Robot::ballIntakeArm.restrictPosition(100);
    ballIntakeArm.setBrakeMode();
    driveBase.setCoastMode();
}

void Robot::TeleopPeriodic() {
    frc::Scheduler::GetInstance()->Run();
    
    //LimitSwitchReset();

    int value = oi.js0->GetPOV();
    if(value == 180 && previousPovValue != 180){
        //frc::Command *cmd = new ClimbCommandGroup();
        //cmd->Start();
    }
    previousPovValue = value;
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

void Robot::LimitSwitchReset(){
    bool isPressed = ballIntakeArm.isTopLimitSwitchPressed();
    if (isPressed && !wasPressed) {
        hasEverResetBallIntakeArm = true;
        frc::Command *cmd = new ResetIntakeArmPosCG();
        cmd->Start();
    }
    wasPressed = isPressed;
}

void Robot::DefaultSolonoidState(){
    static bool hasBeenReset = false;

    if (hasBeenReset) {
        return;
    }

    driveBase.setCoastMode();
    ballIntakeArm.setCoastMode();
    ballShooter.retractPiston();
    hatchPanelClaw.retractClaw();
    hasBeenReset = true;
}