#include "commands/ClimbCommandGroup.h"
#include <commands/DriveTrainBrakeMode.h>
#include <commands/ClimbBallIntakePositionCommand.h>
#include <commands/MoveIntakeArmCommand.h>
#include <commands/MoveIntakeArmPercentageCommand.h>
#include <commands/MoveIntakeArmTimeCommand.h>
#include <frc/commands/WaitCommand.h>
#include <commands/StopIntakeArmCommand.h>

ClimbCommandGroup::ClimbCommandGroup() {
  //AddSequential(new DriveTrainBrakeMode(true));
  //AddSequential(new MoveIntakeArmTimeCommand(-0.2, 0.75));
}
