/*
AlmostRandom generates random number from a few entropy sources within the Arduino.
Copyright (C) 2024 cygig

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; 
either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; 
if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
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
    #if defined(CONFIG_IDF_TARGET_ESP32S3)
      void setRanclock(uint32_t* myTimerACountAddress, uint32_t* myTimerBCountAddress);
      void setLatch(uint32_t* myTimerALatchAddress, uint32_t* myTimerBLatchAddress);
    #else
      void setRanclock(byte* myTimerACountAddress, byte* myTimerBCountAddress);
    #endif
    
    byte getRanclock();
    byte getLastRanclock();


    void enableRainput(bool myEnable);
    bool isEnabledRainput();
    byte getRainput();
    byte getLastRainput();

    static char* toBin(unsigned long myLong, byte bitCount);


    
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
    #if defined(CONFIG_IDF_TARGET_ESP32S3)
      // Seems like I can only read the esp32s3 registers using a 32bit pointer
      uint32_t *timerALatchAddress, *timerBLatchAddress;
      uint32_t *timerACountAddress, *timerBCountAddress;
    #else
      // These are for the default 8-bit registers
      byte *timerACountAddress, *timerBCountAddress;  
    #endif

};

#endif
