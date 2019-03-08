/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LockClawTimeCG.h"
#include <commands/LockClawCommand.h>
#include <frc/commands/WaitCommand.h>

LockClawTimeCG::LockClawTimeCG(double sec) {
  AddSequential(new frc::WaitCommand(sec));
  AddSequential(new LockClawCommand());
}
