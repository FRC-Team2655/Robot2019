#include "commands/PlaceHatchPanelCG.h"
#include <frc/commands/WaitCommand.h>
#include <commands/ClawExtendCommand.h>
#include <commands/DrivePercentageTimeCommand.h>
#include <commands/DirectOpenClawCommand.h>
#include <commands/DirectCloseClawCommand.h>

PlaceHatchPanelCG::PlaceHatchPanelCG() {
  AddSequential(new ClawExtendCommand(true));
  //AddSequential(new DriveDistanceCommand(-12));
  AddSequential(new DirectOpenClawCommand());
  AddSequential(new frc::WaitCommand(2));
  //AddSequential(new DriveDistanceCommand(12));
  AddSequential(new DirectCloseClawCommand());
}