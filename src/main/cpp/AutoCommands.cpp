#include <team2655/autonomous.hpp>
#include <AutoCommands.h>
#include <iostream>
#include <string>
#include <Robot.h>

void DriveCommand::start(std::string cmdName, std::vector<std::string> args){
    // Make sure there are enough arguments
    if(arguments.size() < 1){
        // Not enough arguments. Complete and exit function
        complete();
        return;
    }
    // Set the timeout for command based on the arguments
    setTimeout((int)(stod(arguments[0]) * 1000));
}

void DriveCommand::process(){
    double power;
    if(commandName == "drive_forward"){
        power = 0.5;
    }else{
        power = -0.5;
    }
    Robot::currentRobot->driveBase.drivePercentage(power, 0);
}

void DriveCommand::handleComplete(){
    Robot::currentRobot->driveBase.drivePercentage(0, 0);
}