#include "AlmostRandom.h"

void AlmostRandom::enableRanclock(bool myEnable)
{
  flags.enableRanclock=myEnable;
}



bool AlmostRandom::isEnabledRanclock()
{
  return flags.enableRanclock;
}



void AlmostRandom::setRanclock(byte* myTimerACountAddress, byte* myTimerBCountAddress)
{
  timerACountAddress = myTimerACountAddress;
  timerBCountAddress = myTimerBCountAddress;
}



byte AlmostRandom::getRanclock()
{
  // Early return if ranclock is disabled
  if (flags.enableRanclock==false) return 0;

  byte result=0;
  unsigned int timerACount = *timerACountAddress;
  unsigned int timerBCount = *timerBCountAddress;
  
  result = timerACount ^ timerBCount;

  ranclockByte = result;
  return result;
}



byte AlmostRandom::getLastRanclock()
{
  return ranclockByte;  
}