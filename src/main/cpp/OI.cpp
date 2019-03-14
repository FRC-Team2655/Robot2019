#include "OI.h"
#include <frc/WPILib.h>

#include <commands/MoveIntakeArmCommand.h>
#include <commands/ResetAllCommand.h>
#include <commands/FireShooterPistonCommand.h>
#include <commands/CloseClawCommand.h>
#include <commands/ShootCargoShipCommandGroup.h>
#include <commands/MoveShooterWheelsCommand.h>
#include <commands/ToggleClawExtensionCommand.h>
#include <commands/ShootRocketLvl2CG.h>
#include <commands/ClimbBallIntakePositionCommand.h>
#include <commands/ClimbCommandGroup.h>
#include <commands/JoystickBallIntakeDriveCommand.h>
#include <commands/SetAtRocketHeightCommand.h>
#include <commands/PositionBasedShootCommand.h>
#include <RobotMap.h>

using namespace team2655;

OI::OI() {
  js0 = new frc::Joystick(0);
  //js1 = new frc::Joystick(1);
  frc::JoystickButton *xBtn = new frc::JoystickButton(js0, 2);
  frc::JoystickButton *squareBtn = new frc::JoystickButton(js0, 1);
  frc::JoystickButton *optionBtn = new frc::JoystickButton(js0, 10);
  frc::JoystickButton *r2Btn = new frc::JoystickButton(js0, 8);
  frc::JoystickButton *l1Btn = new frc::JoystickButton(js0, 5);
  frc::JoystickButton *r1Btn = new frc::JoystickButton(js0, 6);
  frc::JoystickButton *triangleBtn = new frc::JoystickButton(js0, 4);
  frc::JoystickButton *circleBtn = new frc::JoystickButton(js0, 3);
  frc::JoystickButton *shareBtn = new frc::JoystickButton(js0, 9);
  frc::JoystickButton *l2Btn = new frc::JoystickButton(js0, 7);

  squareBtn->WhenPressed(new ToggleClawExtensionCommand());
  r2Btn->WhenPressed(new CloseClawCommand(false));
  r2Btn->WhenReleased(new CloseClawCommand(true));
  //optionBtn->WhenPressed(new ResetAllCommand());
  r1Btn->WhileHeld(new MoveShooterWheelsCommand(.4, true));


  l1Btn->WhileHeld(new PositionBasedShootCommand());

  triangleBtn->WhenPressed(new MoveIntakeArmCommand(-0.12));
  triangleBtn->WhenPressed(new SetAtRocketHeightCommand(true));
  xBtn->WhenPressed(new MoveIntakeArmCommand(BallIntakeUpPos));
  xBtn->WhenPressed(new SetAtRocketHeightCommand(false));
  circleBtn->WhenPressed(new MoveIntakeArmCommand(-0.265));
  circleBtn->WhenPressed(new SetAtRocketHeightCommand(false));
  l2Btn->WhenPressed(new JoystickBallIntakeDriveCommand());
  l2Btn->WhenPressed(new SetAtRocketHeightCommand(false));
}