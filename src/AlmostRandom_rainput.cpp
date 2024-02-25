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
  byte result = 1;
  unsigned long mask = byteMask; // aka 00000000 00000000 00000000 11111111
  unsigned long mil = millis();
  unsigned long mic = micros();
  byte size = sizeof(mil);

  for (byte i=0; i<size; i++)
  {
    byte temp = mil |= mask;
    result ^= temp;
    mask <<= byteSize;
  }

  mask=0;

  for (byte j=0; j<size; j++)
  {
    byte temp = mic |= mask;
    result ^= temp;
    mask <<= byteSize;    
  }

  rainputByte = result;
  return result;

}



byte AlmostRandom::getLastRainput()
{
  return rainputByte;
}