////////////////////////////////////////////////////////////////////////////////
/// @file OperatorController.ino
///
/// @brief Operator controller firmware for Argos team 1756's 2019 robot
///
/// @author David Turner (dkt01)
///
/// @copyright This file is part of 2019-Robot
///            (https://github.com/FRC1756-Argos/2019-Robot).
/// @copyright 2019-Robot is free software: you can redistribute it and/or modify
///            it under the terms of the GNU General Public License as published by
///            the Free Software Foundation, either version 3 of the License, or
///            (at your option) any later version.
/// @copyright 2019-Robot is distributed in the hope that it will be useful,
///            but WITHOUT ANY WARRANTY; without even the implied warranty of
///            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///            GNU General Public License for more details.
/// @copyright You should have received a copy of the GNU General Public License
///            along with 2019-Robot.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////

#include <Joystick.h>
#include "DebouncedButtonSet.h"

constexpr int numOutputButtons = 20;

DebouncedButtonSet<20> inputs( { DebouncedDigitalInput( 0, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 1, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 2, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 3, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 4, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 5, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 6, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 7, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 8, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 9, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 10, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 11, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 12, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 13, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 14, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 15, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 16, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 17, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 18, // Pin number
                                                        (bool)true ), // Use internal pullup
                                 DebouncedDigitalInput( 19, // Pin number
                                                        (bool)true ) // Use internal pullup
                               } );

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  numOutputButtons, 0,   // Button Count, Hat Switch Count
  false, false, false,   // No X, Y, or Z axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  inputs.Initialize();
  inputs.SetDebounceCount(5);

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  static int currentButton = 0;

  inputs.Update();

  // Read pin values
  for (int index = 0; index < numOutputButtons; index++)
  {
    Joystick.setButton(index, index == currentButton);
  }

  ++currentButton;

  if(currentButton >= numOutputButtons)
  {
    currentButton = 0;
  }

  delay(500);
}
