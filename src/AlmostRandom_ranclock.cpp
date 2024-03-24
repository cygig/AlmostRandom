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

void AlmostRandom::enableRanclock(bool myEnable)
{
  flags.enableRanclock=myEnable;
}



bool AlmostRandom::isEnabledRanclock()
{
  return flags.enableRanclock;
}







#if defined(CONFIG_IDF_TARGET_ESP32S3)
  void AlmostRandom::setLatch(uint32_t* myTimerALatchAddress, uint32_t* myTimerBLatchAddress)
  {
    timerALatchAddress = myTimerALatchAddress;
    timerBLatchAddress = myTimerBLatchAddress;
  }

  void AlmostRandom::setRanclock(uint32_t* myTimerACountAddress, uint32_t* myTimerBCountAddress)
  {
    timerACountAddress = myTimerACountAddress;
    timerBCountAddress = myTimerBCountAddress;
  }
#else
  void AlmostRandom::setRanclock(byte* myTimerACountAddress, byte* myTimerBCountAddress)
  {
    timerACountAddress = myTimerACountAddress;
    timerBCountAddress = myTimerBCountAddress;
  }
#endif



byte AlmostRandom::getRanclock()
{
  // Early return if ranclock is disabled
  if (flags.enableRanclock==false) return 0;

  #if defined(CONFIG_IDF_TARGET_ESP32S3)
    *timerALatchAddress=1;
    *timerBLatchAddress=1;
  #endif 

  byte result=0;
  byte timerACount = *timerACountAddress;
  byte timerBCount = *timerBCountAddress;
  
  result = timerACount ^ timerBCount;

  ranclockByte = result;
  return result;
}



byte AlmostRandom::getLastRanclock()
{
  return ranclockByte;  
}