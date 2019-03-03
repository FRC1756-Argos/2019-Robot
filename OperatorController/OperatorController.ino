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
#include "IndicatorLights.h"
#include "PinMapping.h"

constexpr int numOutputButtons = 18;
constexpr uint16_t debounceSamples = 5;

DebouncedButtonSet<18> inputs( { DebouncedDigitalInput( OCInputs::button_feeder_in, // Input pin number
                                                        OCInputs::button_feeder_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_depot_in, // Input pin number
                                                        OCInputs::button_depot_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_nearRocketLow_in, // Input pin number
                                                        OCInputs::button_nearRocketLow_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_nearRocketMid_in, // Input pin number
                                                        OCInputs::button_nearRocketMid_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_nearRocketHigh_in, // Input pin number
                                                        OCInputs::button_nearRocketHigh_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_farRocketLow_in, // Input pin number
                                                        OCInputs::button_farRocketLow_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_farRocketMid_in, // Input pin number
                                                        OCInputs::button_farRocketMid_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_farRocketHigh_in, // Input pin number
                                                        OCInputs::button_farRocketHigh_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_cargoShip_in, // Input pin number
                                                        OCInputs::button_cargoShip_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::switch_cargoHatch_in, // Input pin number
                                                        OCInputs::switch_cargoHatch_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::switch_climb_in, // Input pin number
                                                        OCInputs::switch_climb_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::switch_leftRight_in, // Input pin number
                                                        OCInputs::switch_leftRight_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_unassigned1_in, // Input pin number
                                                        OCInputs::button_unassigned1_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_unassigned2_in, // Input pin number
                                                        OCInputs::button_unassigned2_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_unassigned3_in, // Input pin number
                                                        OCInputs::button_unassigned3_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::button_unassigned4_in, // Input pin number
                                                        OCInputs::button_unassigned4_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::switch_unassigned1_in, // Input pin number
                                                        OCInputs::switch_unassigned1_gnd, // Ground pin number
                                                        (bool)true ),
                                 DebouncedDigitalInput( OCInputs::switch_unassigned2_in, // Input pin number
                                                        OCInputs::switch_unassigned2_gnd, // Ground pin number
                                                        (bool)true ),
                               } );

IndicatorLights<22> leds( { LED( OCOutputs::led_button_feeder_out,
                                 OCOutputs::led_button_feeder_gnd,
                                 OCOutputs::led_button_feeder_pwm ),
                            LED( OCOutputs::led_button_depot_out,
                                 OCOutputs::led_button_depot_gnd,
                                 OCOutputs::led_button_depot_pwm ),
                            LED( OCOutputs::led_button_nearRocketLow_out,
                                 OCOutputs::led_button_nearRocketLow_gnd,
                                 OCOutputs::led_button_nearRocketLow_pwm ),
                            LED( OCOutputs::led_button_nearRocketMid_out,
                                 OCOutputs::led_button_nearRocketMid_gnd,
                                 OCOutputs::led_button_nearRocketMid_pwm ),
                            LED( OCOutputs::led_button_nearRocketHigh_out,
                                 OCOutputs::led_button_nearRocketHigh_gnd,
                                 OCOutputs::led_button_nearRocketHigh_pwm ),
                            LED( OCOutputs::led_button_farRocketLow_out,
                                 OCOutputs::led_button_farRocketLow_gnd,
                                 OCOutputs::led_button_farRocketLow_pwm ),
                            LED( OCOutputs::led_button_farRocketMid_out,
                                 OCOutputs::led_button_farRocketMid_gnd,
                                 OCOutputs::led_button_farRocketMid_pwm ),
                            LED( OCOutputs::led_button_farRocketHigh_out,
                                 OCOutputs::led_button_farRocketHigh_gnd,
                                 OCOutputs::led_button_farRocketHigh_pwm ),
                            LED( OCOutputs::led_button_cargoShip_out,
                                 OCOutputs::led_button_cargoShip_gnd,
                                 OCOutputs::led_button_cargoShip_pwm ),
                            LED( OCOutputs::led_switch_climb_out,
                                 OCOutputs::led_switch_climb_gnd,
                                 OCOutputs::led_switch_climb_pwm ),
                            LED( OCOutputs::led_switch_cargoHatch_Cargo_out,
                                 OCOutputs::led_switch_cargoHatch_Cargo_gnd,
                                 OCOutputs::led_switch_cargoHatch_Cargo_pwm ),
                            LED( OCOutputs::led_switch_cargoHatch_Hatch_out,
                                 OCOutputs::led_switch_cargoHatch_Hatch_gnd,
                                 OCOutputs::led_switch_cargoHatch_Hatch_pwm ),
                            LED( OCOutputs::led_switch_leftRight_Left_out,
                                 OCOutputs::led_switch_leftRight_Left_gnd,
                                 OCOutputs::led_switch_leftRight_Left_pwm ),
                            LED( OCOutputs::led_switch_leftRight_Right_out,
                                 OCOutputs::led_switch_leftRight_Right_gnd,
                                 OCOutputs::led_switch_leftRight_Right_pwm ),
                            LED( OCOutputs::led_button_unassigned1_out,
                                 OCOutputs::led_button_unassigned1_gnd,
                                 OCOutputs::led_button_unassigned1_pwm ),
                            LED( OCOutputs::led_button_unassigned2_out,
                                 OCOutputs::led_button_unassigned2_gnd,
                                 OCOutputs::led_button_unassigned2_pwm ),
                            LED( OCOutputs::led_button_unassigned3_out,
                                 OCOutputs::led_button_unassigned3_gnd,
                                 OCOutputs::led_button_unassigned3_pwm ),
                            LED( OCOutputs::led_button_unassigned4_out,
                                 OCOutputs::led_button_unassigned4_gnd,
                                 OCOutputs::led_button_unassigned4_pwm ),
                            LED( OCOutputs::led_switch_unassigned1_OFF_out,
                                 OCOutputs::led_switch_unassigned1_OFF_gnd,
                                 OCOutputs::led_switch_unassigned1_OFF_pwm ),
                            LED( OCOutputs::led_switch_unassigned1_ON_out,
                                 OCOutputs::led_switch_unassigned1_ON_gnd,
                                 OCOutputs::led_switch_unassigned1_ON_pwm ),
                            LED( OCOutputs::led_switch_unassigned2_OFF_out,
                                 OCOutputs::led_switch_unassigned2_OFF_gnd,
                                 OCOutputs::led_switch_unassigned2_OFF_pwm ),
                            LED( OCOutputs::led_switch_unassigned2_ON_out,
                                 OCOutputs::led_switch_unassigned2_ON_gnd,
                                 OCOutputs::led_switch_unassigned2_ON_pwm ),
                          },
                          10 );

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  numOutputButtons, 0,   // Button Count, Hat Switch Count
  false, false, false,   // No X, Y, or Z axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  inputs.Initialize();
  inputs.SetDebounceCount(debounceSamples);
  leds.Initialize();
  for(size_t i = 0; i < leds.GetNumLights(); ++i)
  {
    leds.SetPattern(i, LED::LEDPattern::PULSE_FAST);
  }

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  inputs.Update();
  leds.Update();

  const bool feederVal = inputs.GetValue(OCInputs::button_feeder_idx);
  leds.Set(OCOutputs::led_button_feeder_idx, feederVal);

  const bool depotVal = inputs.GetValue(OCInputs::button_depot_idx);
  leds.Set(OCOutputs::led_button_depot_idx, depotVal);

  const bool nearRocketLowVal = inputs.GetValue(OCInputs::button_nearRocketLow_idx);
  leds.Set(OCOutputs::led_button_nearRocketLow_idx, nearRocketLowVal);

  const bool nearRocketMidVal = inputs.GetValue(OCInputs::button_nearRocketMid_idx);
  leds.Set(OCOutputs::led_button_nearRocketMid_idx, nearRocketMidVal);

  const bool nearRocketHighVal = inputs.GetValue(OCInputs::button_nearRocketHigh_idx);
  leds.Set(OCOutputs::led_button_nearRocketHigh_idx, nearRocketHighVal);

  const bool farRocketLowVal = inputs.GetValue(OCInputs::button_farRocketLow_idx);
  leds.Set(OCOutputs::led_button_farRocketLow_idx, farRocketLowVal);

  const bool farRocketMidVal = inputs.GetValue(OCInputs::button_farRocketMid_idx);
  leds.Set(OCOutputs::led_button_farRocketMid_idx, farRocketMidVal);

  const bool farRocketHighVal = inputs.GetValue(OCInputs::button_farRocketHigh_idx);
  leds.Set(OCOutputs::led_button_farRocketHigh_idx, farRocketHighVal);

  const bool cargoShipVal = inputs.GetValue(OCInputs::button_cargoShip_idx);
  leds.Set(OCOutputs::led_button_cargoShip_idx, cargoShipVal);

  const bool unassigned1Val = inputs.GetValue(OCInputs::button_unassigned1_idx);
  leds.Set(OCOutputs::led_button_unassigned1_idx, unassigned1Val);

  const bool unassigned2Val = inputs.GetValue(OCInputs::button_unassigned2_idx);
  leds.Set(OCOutputs::led_button_unassigned2_idx, unassigned2Val);

  const bool unassigned3Val = inputs.GetValue(OCInputs::button_unassigned3_idx);
  leds.Set(OCOutputs::led_button_unassigned3_idx, unassigned3Val);

  const bool unassigned4Val = inputs.GetValue(OCInputs::button_unassigned4_idx);
  leds.Set(OCOutputs::led_button_unassigned4_idx, unassigned4Val);

  const bool climbVal = inputs.GetValue(OCInputs::switch_climb_idx);
  leds.Set(OCOutputs::led_switch_climb_idx, climbVal);

  const bool cargoHatchVal = inputs.GetValue(OCInputs::switch_cargoHatch_idx);
  leds.Set(OCOutputs::led_switch_cargoHatch_Cargo_idx, cargoHatchVal);
  leds.Set(OCOutputs::led_switch_cargoHatch_Hatch_idx, !cargoHatchVal);

  const bool leftRightVal = inputs.GetValue(OCInputs::switch_leftRight_idx);
  leds.Set(OCOutputs::led_switch_leftRight_Left_idx, leftRightVal);
  leds.Set(OCOutputs::led_switch_leftRight_Right_idx, !leftRightVal);

  const bool unassigned1SWVal = inputs.GetValue(OCInputs::switch_unassigned1_idx);
  leds.Set(OCOutputs::led_switch_unassigned1_ON_idx, unassigned1SWVal);
  leds.Set(OCOutputs::led_switch_unassigned1_OFF_idx, !unassigned1SWVal);

  const bool unassigned2SWVal = inputs.GetValue(OCInputs::switch_unassigned2_idx);
  leds.Set(OCOutputs::led_switch_unassigned2_ON_idx, unassigned2SWVal);
  leds.Set(OCOutputs::led_switch_unassigned2_OFF_idx, !unassigned2SWVal);


  // Read pin values
  for (int index = 0; index < numOutputButtons; index++)
  {
    Joystick.setButton(index, inputs.GetValue(index));
  }
}
