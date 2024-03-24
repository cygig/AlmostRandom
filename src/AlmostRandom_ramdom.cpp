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

void AlmostRandom::enableRamdom(bool myEnable)
{
  flags.enableRamdom = myEnable;
}



bool AlmostRandom::isEnabledRamdom()
{
  return flags.enableRamdom;
}



void AlmostRandom::setRamdom(byte* myRamStart, byte* myRamEnd)
{
  // Ramend must be bigger
  if (myRamEnd >= myRamStart)
  {
    ramStart = myRamStart;
    ramEnd = myRamEnd;
  }
}



byte AlmostRandom::getRamdom()
{
  // Early return if ramdom is disabled
  if (flags.enableRamdom==false) return 0;

  byte result=0;
  for (byte* i=ramStart; i<=ramEnd; i++)
  {
    byte value = *i;
    result ^= value;
  }

  ramdomByte = result;
  return result;
}



byte AlmostRandom::getLastRamdom()
{
  return ramdomByte;  
}