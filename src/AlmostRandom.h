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
     byte randomByte;
     byte ranalogByte;
     byte ramdomByte;
     byte ranclockByte;
     
     struct Flags
     {
      bool isEnabledRanalog : 1;
      bool isEnabledRamdom : 1;
      bool isEnabledRanclock : 1;
     } flags;

    byte analogPins[8];

    byte* ramStart, ramEnd;

    byte* clockAddressA, clockAddressB;



};

#endif
