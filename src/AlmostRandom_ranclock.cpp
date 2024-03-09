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



#if defined(CONFIG_IDF_TARGET_ESP32S3)
  void AlmostRandom::setLatch(byte* myTimerALatchAddress, byte* myTimerBLatchAddress)
  {
    timerALatchAddress = myTimerALatchAddress;
    timerBLatchAddress = myTimerBLatchAddress;
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
  unsigned int timerACount = *timerACountAddress;
  unsigned int timerBCount = *timerBCountAddress;

  Serial.println(timerACount);
  Serial.println(timerBCount);
  
  result = timerACount ^ timerBCount;

  ranclockByte = result;
  return result;
}



byte AlmostRandom::getLastRanclock()
{
  return ranclockByte;  
}