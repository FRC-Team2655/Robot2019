#include "commands/PlaceHatchPanelCG.h"
#include <commands/DriveDistanceCommand.h>
#include <commands/CloseClawCommand.h>
#include <frc/commands/WaitCommand.h>
#include <commands/ExtendClawCommand.h>
#include <commands/DrivePercentageTimeCommand.h>
#include <commands/DirectOpenClawCommand.h>
#include <commands/DirectCloseClawCommand.h>

PlaceHatchPanelCG::PlaceHatchPanelCG() {
  AddSequential(new ExtendClawCommand(true));
  AddSequential(new DrivePercentageTimeCommand(-0.1, 0.8));
  AddSequential(new DirectOpenClawCommand());
  AddSequential(new frc::WaitCommand(2));
  AddSequential(new DrivePercentageTimeCommand(0.1, 0.8));
  AddSequential(new DirectCloseClawCommand());
}