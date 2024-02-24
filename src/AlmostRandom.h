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
  private: 
    const static byte byteSize = 8; // size of one byte
     byte randomByte=0;
     byte ranalogByte=0;
     byte ramdomByte=0;
     byte ranclockByte=0;

     struct Flags
     {
      bool enableRanalog : 1;
      bool enableRamdom : 1;
      bool enableRanclock : 1;
      bool evenIsZero : 1;
     } flags;

    // Ranalog
    byte analogPins[byteSize];

    // Ramdom
    byte* ramStart, ramEnd;

    // Ranclock
    byte* timerACountAddress, timerBCountAddress;


  public:
    AlmostRandom();
    byte getRandomByte();
    byte getLastRandomByte();

    int16_t getRandomInt();
    uint16_t getRandomUInt();
    int32_t getRandomLong();
    uint32_t getRandomULong();
    float getRandomFloat();


    void enableRanalog(bool myEnable);
    bool isEnabledRanalog();
    void setRanalog(byte myAnalogPin);
    void setRanalog(byte myAnalogPins[byteSize]);
    void setEvenIsZero(bool myEvenIsZero);
    bool isEvenZero();
    byte getRanalog();
    byte getLastRanalog();

    void enableRamdom(bool myEnable);
    bool isEnabledRamdom();
    void setRamdom(byte* ramStart, byte* ramEnd);
    byte getRamdom();
    byte getLastRamdom();

    void enableRanclock(bool myEnable);
    bool isEnabledRanclock();
    void setRanclock(byte* clockAddressA, byte* clockAddressB);
    byte getRanclock();
    byte getLastRanclock();
    




};

#endif
