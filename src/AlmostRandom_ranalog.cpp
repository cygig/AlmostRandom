#include "AlmostRandom.h"

void AlmostRandom::enableRanalog()
{
  flags.enableRanalog = true;  
}



void AlmostRandom::disableRanalog()
{
  flags.enableRanalog = false; 
}



void AlmostRandom::setRanalog(byte myAnalogPin)
{
  for (byte i=0; i<byteSize; i++){ analogPins[i]=myAnalogPin; }
}



void AlmostRandom::setRanalog(byte myAnalogPins[byteSize])
{
  for (byte i=0; i<byteSize; i++){ analogPins[i]=myAnalogPins[i]; }
}

void AlmostRandom::setEvenIsZero(bool myEvenIsZero)
{
  flags.evenIsZero = myEvenIsZero;
}



bool AlmostRandom::isEvenZero()
{
  return flags.isEvenZero;
}

byte AlmostRandom::getRanalog()
{
  byte result=0;
  byte resultMask=1;

  for (byte i=0; i<byteSize; i++)
  {
    unsigned int reading = analogRead(analogPins[i]);
    bool readingIsEven = (reading%2==0) ? true : false;

    // Early return, if result is even and even is zero, or if result is odd and odd is zero, 
    // no need to write anything since result is all zeros to begin with
    if (readingIsEven && flags.isEvenZero) continue;
    if (!readingIsEven && !flags.isEvenZero) continue;

    // Set bit and advance the mask
    result |= resultMask;
    resultMask <<=1;
  }

  ranalogByte = result;
  return result;
}


byte AlmostRandom::getLastRanalog()
{
  return ranalogByte;
}