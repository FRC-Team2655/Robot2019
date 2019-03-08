#include "commands/PlaceHatchPanelCG.h"
#include <commands/DriveDistanceCommand.h>
#include <commands/CloseClawCommand.h>
#include <frc/commands/WaitCommand.h>

PlaceHatchPanelCG::PlaceHatchPanelCG() {
  AddSequential(new DriveDistanceCommand(-12));
  AddSequential(new CloseClawCommand(false));
  AddSequential(new frc::WaitCommand(2));
  AddSequential(new DriveDistanceCommand(12));
}