////////////////////////////////////////////////////////////////////////////////
/// @file DebouncedDigitalInput.h
///
/// @brief Abstracted digital input with debouncing applied
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

#include "DebouncedDigitalInput.h"
#include <Arduino.h>

DebouncedDigitalInput::DebouncedDigitalInput( uint8_t pinNumber,
                                              bool    usePullup ) : DebouncedDigitalInput(pinNumber, 0, usePullup)
{
  // Do nothing
}

DebouncedDigitalInput::DebouncedDigitalInput( uint8_t  pinNumber,
                                              uint16_t debounceSamples,
                                              bool     usePullup ) : m_pinNumber(pinNumber),
                                                                     m_usePullup(usePullup),
                                                                     m_debounceSamples(debounceSamples),
                                                                     m_initialized(false),
                                                                     m_debounceCount(0),
                                                                     m_rawValue(false),
                                                                     m_debouncedValue(false)
{
  // Do nothing
}

void DebouncedDigitalInput::Initialize()
{
  pinMode(m_pinNumber, m_usePullup ? INPUT_PULLUP : INPUT);
  m_initialized = true;
}

bool DebouncedDigitalInput::Update()
{
  if(false == m_initialized)
  {
    return false;
  }

  m_rawValue = (digitalRead(m_pinNumber) == HIGH);
  if(m_rawValue != m_debouncedValue)
  {
    ++m_debounceCount;
    if(m_debounceCount >= m_debounceSamples)
    {
      m_debouncedValue = m_rawValue;
      m_debounceCount = 0;
    }
  }
  else
  {
    m_debounceCount = 0;
  }

  return m_debouncedValue;
}

bool DebouncedDigitalInput::GetValue() const
{
  return m_debouncedValue;
}

bool DebouncedDigitalInput::GetRawValue() const
{
  return m_rawValue;
}

void DebouncedDigitalInput::Reset(bool newValue)
{
  m_rawValue = newValue;
  m_debouncedValue = newValue;
  m_debounceCount = 0;
}

void DebouncedDigitalInput::SetDebounceCount(uint16_t newCount)
{
  m_debounceSamples = newCount;
  if(m_debounceSamples <= m_debounceCount)
  {
    m_debouncedValue = m_rawValue;
    m_debounceCount = 0;
  }
}
