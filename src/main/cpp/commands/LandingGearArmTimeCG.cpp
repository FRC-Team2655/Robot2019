/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LandingGearArmTimeCG.h"
#include <commands/MoveLandingGearCommand.h>
#include <commands/StopLandingGearArmCommand.h>
#include <frc/commands/WaitCommand.h>

LandingGearArmTimeCG::LandingGearArmTimeCG(double speed, double timeSec) {
  MoveLandingGearCommand *command = new MoveLandingGearCommand(speed, false);
  AddParallel(command);
  AddSequential(new frc::WaitCommand(timeSec));
  AddSequential(new StopLandingGearArmCommand());
}
