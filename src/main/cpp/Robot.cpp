#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <team2655/autonomous.hpp>
#include <commands/ExecutePathCommand.h>
#include <commands/MoveIntakeArmCommand.h>

#include <commands/ResetIntakeArmPosCG.h>
#include <commands/WaitAutoCommand.h>
#include <commands/CloseClawCommand.h>
#include <commands/UnlockClawCommand.h>
#include <commands/DriveDistanceCommand.h>
#include <commands/RunPlaceHatchCommand.h>
#include <commands/MoveShooterWheelsCommand.h>
#include <commands/DrivePercentageTimeCommand.h>

#include <ctime>

OI Robot::oi;
DriveBaseSubsystem Robot::driveBase;
BallIntakeArmSubsystem Robot::ballIntakeArm;
BallShooterSubsystem Robot::ballShooter;
HatchPanelClawSubsystem Robot::hatchPanelClaw;
bool Robot::hasEverResetBallIntakeArm = false;

void Robot::RobotInit() {
    // Register auto commands
    autoManager.registerCommand(team2655::CommandCreator<ExecutePathCommand>, false, "PATH");
    autoManager.registerCommand(team2655::CommandCreator<WaitAutoCommand>, false, "WAIT");
    autoManager.registerCommand(team2655::CommandCreator<RunPlaceHatchCommand>, false, "PLACE_HATCH");

    autoPosition.AddDefault("No Auto", 0);
    autoPosition.AddObject("Left - Front CS", 1);
    autoPosition.AddObject("Right - Front CS", 2);
}

void Robot::RobotPeriodic() {
    frc::SmartDashboard::PutNumber(LeftVelocity, driveBase.getLeftVelocity());
    frc::SmartDashboard::PutNumber(RightVelocity, driveBase.getRightVelocity());
    frc::SmartDashboard::PutNumber(ArmPosition, ballIntakeArm.getArmPosition());
    frc::SmartDashboard::PutBoolean("LimitSwitchPressed", ballIntakeArm.isTopLimitSwitchPressed());
    frc::SmartDashboard::PutNumber("Intake Arm Vecolity: ", ballIntakeArm.getArmVelocity());
    frc::SmartDashboard::PutNumber("IMU Angle: ", driveBase.getIMUAngle());
    frc::SmartDashboard::PutData("Auto Routine", &autoPosition);
}

void Robot::DisabledInit() {
    driveBase.setBrakeMode(); 
    ballIntakeArm.setBrakeMode();
}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::AutonomousInit() {

    compressor.SetClosedLoopControl(false);
    compressor.SetClosedLoopControl(true);

    driveBase.resetIMUReverse();

    wasPressed = false; // Make sure lock will reengage if limit switch is held when enabled
    DefaultSolonoidState();
    driveBase.setBrakeMode();
    ballIntakeArm.setCoastMode();

    autoManager.clearCommands();
    if(autoPosition.GetSelected() == 1)
        autoManager.loadScript("/auto-scripts/MiddleTop.csv");
    if(autoPosition.GetSelected() == 2)
        autoManager.loadScript("/auto-scripts/MiddleBottom.csv");

    if(autoPosition.GetSelected() != 0){
        autoCommandPtr = autoManager.getScriptCommand();
        autoCommandPtr.get()->Start();
    }

}

void Robot::AutonomousPeriodic() { 
    // Giant button kills auto
    if(oi.js0->GetRawButton(14) && autoCommandPtr.get() != nullptr)
        autoCommandPtr->Cancel();
    LimitSwitchReset();
    frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {

    if (hatchPanelClaw.isExtended()) {
        hatchPanelClaw.lock();
    }

    wasPressed = false; // Make sure lock will reengage if limit switch is held when enabled
    DefaultSolonoidState();

    driveBase.setCoastMode();
    ballIntakeArm.setCoastMode();

    compressor.SetClosedLoopControl(false);
    compressor.SetClosedLoopControl(true);

    std::cout << hatchPanelClaw.extenderSolenoidDirection() << std::endl;
}

void Robot::TeleopPeriodic() {

    frc::Scheduler::GetInstance()->Run();
    
    LimitSwitchReset();

    /*if (oi.js0->GetRawAxis(10)) {
        driveBase.setBrakeMode();
    }else{
        driveBase.setCoastMode();
    }*/

    int value = oi.js0->GetPOV();

    /*std::cout << value << std::endl;

    if (value == 0 && slowIntakeCmd == nullptr) {
        slowIntakeCmd = new MoveShooterWheelsCommand(0.2, false);
        slowIntakeCmd->Start();

        std::cout << "Starting Command..." << std::endl;
    }else if (slowIntakeCmd != nullptr){
        slowIntakeCmd->Cancel();
        slowIntakeCmd = nullptr;
    }*/
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

void Robot::LimitSwitchReset(){
    bool isPressed = ballIntakeArm.isTopLimitSwitchPressed();
    double now = time(NULL);
    if (isPressed && !wasPressed) {
        hasEverResetBallIntakeArm = true;
        frc::Command *cmd = new ResetIntakeArmPosCG();
        cmd->Start();
    }

    // Debounced wasPressed
    if(isPressed){
        lastPressedTime = now;
        wasPressed = true;
    }
    if(now - lastPressedTime >= debounce){
        wasPressed = false; // Only set if not pressed for debounce time
    }
}

void Robot::DefaultSolonoidState(){
    static bool hasBeenReset = false;

    if (hasBeenReset) {
        return;
    }

    ballShooter.retractPiston();
    hatchPanelClaw.retractClaw();
    hatchPanelClaw.closeClaw();
    hatchPanelClaw.unlock();
    hasBeenReset = true;
}