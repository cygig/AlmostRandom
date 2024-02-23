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
    byte getLastRandomByte();

    int16_t getRandomInt();
    uint16_t getRandomUInt();
    int32_t getRandomLong();
    uint32_t getRandomULong();
    float getRandomFloat();


    void enableRanalog();
    void disableRanalog();
    byte setRanalog(byte analogPin);
    byte setRanalog(byte analogPin0, byte analogPin1, 
                    byte analogPin2, byte analogPin3,
                    byte analogPin4, byte analogPin5, 
                    byte analogPin6, byte analogPin7);
    byte getRanalog();
    byte getLastRanalog();

    void enableRamdom();
    void disableRamdom();
    byte setRamdom(byte* ramStart, byte* ramEnd);
    byte getRamdom();
    byte getLastRamdom();

    void enableRanclock();
    void disableRanclock();
    byte setRanclock(byte* clockAddressA, byte* clockAddressB);
    byte getRanclock();
    byte getLastRanclock();
    

  private: 
     byte randomByte=0;
     byte ranalogByte=0;
     byte ramdomByte=0;
     byte ranclockByte=0;
     const static byte byteSize = 8; // size of one byte
     
     struct Flags
     {
      bool isEnabledRanalog : 1;
      bool isEnabledRamdom : 1;
      bool isEnabledRanclock : 1;
     } flags;

    byte analogPins[byteSize];

    byte* ramStart, ramEnd;

    byte* timerACountAddress, timerBCountAddress;



};

#endif
