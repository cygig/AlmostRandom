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