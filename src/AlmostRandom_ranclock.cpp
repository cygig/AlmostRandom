#include "Arduino.h"
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