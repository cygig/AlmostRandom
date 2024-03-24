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

void AlmostRandom::enableRanalog(bool myEnable)
{
  flags.enableRanalog = myEnable;  
}



bool AlmostRandom::isEnabledRanalog()
{
  return flags.enableRanalog; 
}



void AlmostRandom::setRanalog(byte myAnalogPin)
{
  for (byte i=0; i<byteSize; i++){ analogPins[i]=myAnalogPin; }
}



void AlmostRandom::setRanalog(byte myAnalogPins[byteSize])
{
  for (byte i=0; i<byteSize; i++) { analogPins[i]=myAnalogPins[i]; }
}



void AlmostRandom::setEvenIsZero(bool myEvenIsZero)
{
  flags.evenIsZero = myEvenIsZero;
}



bool AlmostRandom::isEvenZero()
{
  return flags.evenIsZero;
}



byte AlmostRandom::getRanalog()
{
  // Early return if ranalog is disabled
  if (flags.enableRanalog==false) return 0;

  byte result=0;
  byte resultMask=1;

  for (byte i=0; i<byteSize; i++)
  {
    unsigned int reading = analogRead(analogPins[i]);
    bool readingIsEven = (reading%2==0) ? true : false;

    // Set bit if reading is even and even is one OR reading is odd and odd is one
    if ( (readingIsEven && !flags.evenIsZero) || (!readingIsEven && flags.evenIsZero))
        result |= resultMask;

    // Advance the mask
    resultMask <<=1;
  }

  ranalogByte = result;
  return result;
}



byte AlmostRandom::getLastRanalog()
{
  return ranalogByte;
}