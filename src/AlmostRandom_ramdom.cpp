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