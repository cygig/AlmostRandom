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

    // Constants
    const static byte byteSize = 8; // size of one byte
    const static byte byteMask = 255; // basically 0b11111111

    byte getRandomByte();
    byte getLastRandomByte();
    byte getLastRunCode();

    int16_t getRandomInt();
    uint16_t getRandomUInt();
    int32_t getRandomLong();
    uint32_t getRandomULong();
    float getRandomFloat();


    void enableRanalog(bool myEnable);
    bool isEnabledRanalog();
    void setRanalog(byte myAnalogPin);
    void setRanalog(byte myAnalogPins[byteSize]);
    void setEvenIsZero (bool myEvenIsZero);
    bool isEvenZero();
    byte getRanalog();
    byte getLastRanalog();

    void enableRamdom(bool myEnable);
    bool isEnabledRamdom();
    void setRamdom(byte* myRamStart, byte* myRamEnd);
    byte getRamdom();
    byte getLastRamdom();

    void enableRanclock(bool myEnable);
    bool isEnabledRanclock();
    void setRanclock(byte* myTimerACountAddress, byte* myTimerBCountAddress);
    byte getRanclock();
    byte getLastRanclock();

    void enableRainput(bool myEnable);
    bool isEnabledRainput();
    byte getRainput();
    byte getLastRainput();

    static char* toBin(unsigned long myLong, byte bitCount);

    void getClockInfo();

    
  private: 
     byte random_Byte=0; // do not confused with ramdomByte
     byte ranalogByte=0;
     byte ramdomByte=0;
     byte ranclockByte=0;
     byte rainputByte=0;

     struct Flags
     {
      bool enableRanalog : 1;
      bool enableRamdom : 1;
      bool enableRanclock : 1;
      bool enableRainput : 1;
      bool evenIsZero : 1;
      byte runCode : 4;
     } flags;

    // Ranalog
    byte analogPins[byteSize];

    // Ramdom
    // This is the correct way to chain declare pointers,
    // byte* ramStart, ramEnd will make ramEnd a normal byte instead of pointer.
    byte *ramStart, *ramEnd;

    // Ranclock
    byte *timerACountAddress, *timerBCountAddress, *timerAControlAddress, *timerBControlAddress;

};

#endif
