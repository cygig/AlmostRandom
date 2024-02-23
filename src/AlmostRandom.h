/*
AlmostRandom by cygig
*/

#ifndef ALMOSTRANDOM_H
#define ALMOSTRANDOM_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif



class AlmostRandom{
  
  public:
    AlmostRandom();
    byte getRandomByte();
    int16_t getRandomInt();
    uint16_t getRandomUInt();

    void enableRanalog();
    void disableRanalog();
    byte setRanalog(unsigned int pin);
    byte getRanalog();

    void enableRamdom();
    void disableRamdom();
    byte setRamdom(byte* ramStart, byte* ramEnd);
    byte getRamdom();

    void enableRanclock();
    void disableRanclock();
    byte setRanclock(byte* clockAddressA, byte* clockAddressB);
    byte getRanclock();
    

  private: 
     byte randomByte;
     
     struct Flags
     {
      bool isEnabledRanalog : 1;
      bool isEnabledRamdom : 1;
      bool isEnabledRanclock : 1;
     } flags;



};

#endif
