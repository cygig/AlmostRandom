/*
AlmostRandom generates random number from a few entropy sources within the Arduino.
Copyright (C) 2024 cygig

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; 
either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; 
if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/



#include "AlmostRandom.h"

void AlmostRandom::enableRainput(bool myEnable)
{
  flags.enableRainput = myEnable;
}



bool AlmostRandom::isEnabledRainput()
{
  return flags.enableRainput;
}



byte AlmostRandom::getRainput()
{
  // Early return if rainput is disabled
  if (flags.enableRainput==false) return 0;

  byte result = 0;
  unsigned long milliz = millis();
  unsigned long microz = micros();
  byte size = sizeof(milliz); // Usually unsigned long is 4 bytes long


  for (byte i=0; i<size; i++)
  {

    // For every iteration, we right shift the reading 8 bits more to capture the last 8 bits
    // We can move a bitmask, but we will need to remove zeros at the end.
    byte shiftCount = byteSize*i;
    unsigned long shiftedMilliz = milliz >> shiftCount;
    unsigned long shiftedMicroz = microz >> shiftCount;

    // We AND the byteMask to get the last 8 bits
    byte tempMilliz = shiftedMilliz & byteMask;
    byte tempMicroz = shiftedMicroz & byteMask;

    // XOR to get mix up the results
    result = result ^ tempMilliz ^ tempMicroz;
  }
  

  rainputByte = result;
  return result;

}



byte AlmostRandom::getLastRainput()
{
  return rainputByte;
}