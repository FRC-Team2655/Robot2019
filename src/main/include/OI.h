#pragma once

#include <frc/Joystick.h>
#include <team2655/joystick.hpp>

using namespace team2655;

class OI {
public:
  OI();
  frc::Joystick *js0;
  frc::Joystick *js1;

  // Configurations for the joystick deadband and cubic function.
  jshelper::AxisConfig driveAxisConfig = jshelper::createAxisConfig(.1, 0, .5);
  jshelper::AxisConfig rotateAxisConfig = jshelper::createAxisConfig(0.1);
  jshelper::AxisConfig ballIntakeAxisConfig = jshelper::createAxisConfig(0.1);
  jshelper::AxisConfig landingGearAxisConfig = jshelper::createAxisConfig(0.1);
};