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



#include "AlmostRandom.h"

// Empty Constructor, we will use setup() instead;
AlmostRandom::AlmostRandom()
{
  
  // The addresses of the timers and ram can be found in the respective datasheets

  // Enable everything first, we disable them later if we do not have the information
  // Rainput is opt-in
  flags.enableRanalog = true;
  flags.enableRamdom = true;
  flags.enableRanclock = true;
  flags.enableRainput = true;
  
  flags.evenIsZero = true;
    

  //== Initialise Analog Pins ==//
  // If A0 is defined, that is usually an assignment to an analog pin, to play safe, we cast it to a byte
  // else just assign all ones, since for ESP32, 0 cannot be used
  #if defined(PIN_A0)
    for (byte i=0; i<byteSize; i++) { analogPins[i]=(byte)A0; }
  #else
    for (byte i=0; i<byteSize; i++) { analogPins[i]=1; }
  #endif



  //== Initialise RAM ==//
  #if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__)
    // 2048 bytes
    ramStart = (byte*)0x0100;
    ramEnd = (byte*)0x08FF;

  #elif defined(__AVR_ATmega32U4__)
    // 2560 bytes
    ramStart = (byte*)0x0100;
    ramEnd = (byte*)0x0AFF;

  #elif defined(__AVR_ATmega2560__)
    // 8192 bytes
    ramStart = (byte*)0x200;
    ramEnd = (byte*)0x21FF;

  #elif defined(__AVR_ATtiny3224__) || defined(__AVR_ATtiny3226__) || defined(__AVR_ATtiny3227__)
    // 3072 bytes
    ramStart = (byte*)0x3400;
    ramEnd = (byte*)0x3FFF;
  
  #elif defined(CONFIG_IDF_TARGET_ESP32S3)
     ramStart = (byte*)0x3FC88000;
     ramEnd = (byte*)0x3FCFFFFF;   

  #elif defined(RAMSTART) && defined(RAMEND)
    // If none of the above MCU, check if RAMSTART and RAMEND are already defined. Typecast for safety.
    ramStart = (byte*)RAMSTART;
    ramEnd = (byte*)RAMEND;

  #else
    // Else we have no idea and users should set the address manually so we disable ramdom first
    ramStart = (byte*)0x0;
    ramEnd = (byte*)0x0;
    flags.enableRamdom=false;
  #endif



  //== Initialise Clock ==//
  #if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__) || \
      defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega2560__)
    timerACountAddress = (byte*)0x46; //8 bit Timer 0
    timerBCountAddress = (byte*)0x84; // 16 bit Timer 1

  #elif defined(__AVR_ATtiny3224__) || defined(__AVR_ATtiny3226__) || defined(__AVR_ATtiny3227__)
    timerACountAddress = (byte*)0xA20; // 0x0A00 + 0x20 Timer A0
    timerBCountAddress = (byte*)0xA9A; // 0x0A90 + 0x0A Timer B1

  #elif defined(CONFIG_IDF_TARGET_ESP32S3)
    // We need a latch for ESP32S2 to update the values into a 32-bit register
    timerACountAddress = (uint32_t*)0x6001F004; // Group 0 Timer 0 Lowest Byte
    timerBCountAddress = (uint32_t*)0x60020004; // Group 1 Timer 0 Lowest Byte
    timerALatchAddress = (uint32_t*)0x6001F00C; // Group 0 Timer 0 Update Address
    timerBLatchAddress = (uint32_t*)0x6002000C; // Group 1 Timer 0 Update Address

  #else
    // Else we have no idea and users should set the address manually so we disable ranclock first
    timerACountAddress = (byte*)0x0;
    timerBCountAddress = (byte*)0x0;
    flags.enableRanclock = false;
  #endif

}



byte AlmostRandom::getRandomByte()
{
  byte result = 0;
  flags.runCode=0;

  if (flags.enableRanalog)
  {
    result ^= getRanalog();
    flags.runCode |= 0b1000;
  }
  
  if (flags.enableRamdom)
  {
    result ^= getRamdom();
    flags.runCode |= 0b0100;
  }
  
  if (flags.enableRanclock)
  {
    result ^= getRanclock();
    flags.runCode |= 0b0010;
  }
  
  if (flags.enableRainput)
  {
    result ^= getRainput();
    flags.runCode |= 0b0001;
  }
  
  random_Byte = result;

  return result;

}



byte AlmostRandom::getLastRandomByte()
{
  return random_Byte;
}



byte AlmostRandom::getLastRunCode()
{
  return flags.runCode;
}



int16_t AlmostRandom::getRandomInt()
{
  return (int16_t)getRandomUInt();
}



uint16_t AlmostRandom::getRandomUInt()
{
  uint16_t result=(uint16_t) getRandomByte();
  result <<= byteSize;
  result |= getRandomByte();

  return result;
}



int32_t AlmostRandom::getRandomLong()
{
  return (int32_t)getRandomULong();
}



uint32_t AlmostRandom::getRandomULong()
{
  const byte byteCount=4;
  uint32_t result=(uint32_t)getRandomByte();
  
  for (byte i=0; i<byteCount-1; i++)
  {
    result <<= byteSize;
    result |= getRandomByte();
  }

  return result;
}



float AlmostRandom::getRandomFloat()
{
  int a = getRandomInt();
  int b = getRandomInt();

  return (float)a / (float)b;
}



char* AlmostRandom::toBin(unsigned long myLong, byte bitCount)
{

  const byte maxBitSize=32; // We handle up to 32 bit or 4 bytes or unsigned long max by default
  uint32_t bitMask = 1; // our mask will be the same size as maxBitSize
  static char result[maxBitSize+1]; // +1 for \0, also static so it remains in ram

  // We force bitCount not to exceed maxSize
  if (bitCount > maxBitSize)
    bitCount = maxBitSize;

  /*
  We start from bitCount-1 element and work our way down to 0.
  bitCount will definitely <= arrary size-1

  Imagine if arraySize is 16. bitCount is 8. 
  0   1   2   3   4   5   6   7   8    9    10  11  12  13  14  15 
  [X] [X] [X] [X] [X] [X] [X] [X] [\0] [ ] [ ] [ ] [ ] [ ] [ ] [ ] 
  
  If masking the bit gives an answer more than zero, that bit is a 1, thurs we write '1'. 
  Then we advance the bitmask.
  */
  for (int i=bitCount-1; i>=0; i--)
  {
    result[i] = ( (myLong & bitMask) > 0 ) ? '1' : '0';
    bitMask <<= 1;
  }

  result[bitCount] = '\0';

  return result;
  
}

