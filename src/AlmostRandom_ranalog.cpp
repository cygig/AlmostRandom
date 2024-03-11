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