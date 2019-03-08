#include "commands/ShootRocketLvl2CG.h"
#include <commands/MoveShooterWheelsCommand.h>
#include <commands/FireShooterPistonCommand.h>
#include <frc/commands/WaitCommand.h>
#include <commands/StopIntakeMotorsCommand.h>

ShootRocketLvl2CG::ShootRocketLvl2CG() {
  AddParallel(new MoveShooterWheelsCommand(1, false));
  AddSequential(new frc::WaitCommand(0));
  AddSequential(new FireShooterPistonCommand(true));
  AddSequential(new frc::WaitCommand(1));
  AddSequential(new StopIntakeMotorsCommand());
  AddSequential(new FireShooterPistonCommand(false));
}
