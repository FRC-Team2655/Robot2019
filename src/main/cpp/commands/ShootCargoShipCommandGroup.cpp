/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootCargoShipCommandGroup.h"
#include <commands/MoveShooterWheelsCommand.h>
#include <commands/FireShooterPistonCommand.h>
#include <frc/commands/WaitCommand.h>
#include <commands/StopIntakeMotorsCommand.h>

ShootCargoShipCommandGroup::ShootCargoShipCommandGroup() {
  AddParallel(new MoveShooterWheelsCommand(0, false));
  AddSequential(new frc::WaitCommand(0));
  AddSequential(new FireShooterPistonCommand(true));
  AddSequential(new frc::WaitCommand(1));
  AddSequential(new StopIntakeMotorsCommand());
  AddSequential(new FireShooterPistonCommand(false));
}
