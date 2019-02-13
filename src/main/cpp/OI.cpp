#include "OI.h"
#include <frc/WPILib.h>

#include <commands/MoveIntakeArmCommand.h>
#include <commands/ResetAllCommand.h>
#include <commands/FireShooterPistonCommand.h>
#include <commands/CloseClawCommand.h>
#include <commands/ShootCargoshipCommandGroup.h>
#include <commands/MoveShooterWheelsCommand.h>
#include <commands/ToggleClawExtensionCommand.h>
#include <commands/ToggleLockCommand.h>
#include <commands/ShootRocketLvl2CG.h>
#include <commands/LandingGearArmTimeCG.h>

using namespace team2655;

OI::OI() {
  js0 = new frc::Joystick(0);
  js1 = new frc::Joystick(1);
  frc::JoystickButton *xBtn = new frc::JoystickButton(js0, 2);
  frc::JoystickButton *squareBtn = new frc::JoystickButton(js0, 1);
  frc::JoystickButton *optionBtn = new frc::JoystickButton(js0, 10);
  frc::JoystickButton *r2Btn = new frc::JoystickButton(js0, 8);
  frc::JoystickButton *l1Btn = new frc::JoystickButton(js0, 5);
  frc::JoystickButton *r1Btn = new frc::JoystickButton(js0, 6);
  frc::JoystickButton *triangleBtn = new frc::JoystickButton(js0, 4);
  frc::JoystickButton *circleBtn = new frc::JoystickButton(js0, 3);

  xBtn->WhenPressed(new ShootCargoShipCommandGroup());
  squareBtn->WhenPressed(new ToggleClawExtensionCommand());
  r2Btn->WhenPressed(new CloseClawCommand(false));
  r2Btn->WhenReleased(new CloseClawCommand(true));
  optionBtn->WhenPressed(new ResetAllCommand());
  r1Btn->WhileHeld(new MoveShooterWheelsCommand(.4, true));
  l1Btn->WhileHeld(new MoveShooterWheelsCommand(1, false));
  triangleBtn->WhenPressed(new MoveIntakeArmCommand(0));
  circleBtn->WhenPressed(new MoveIntakeArmCommand(-0.1875));
}
