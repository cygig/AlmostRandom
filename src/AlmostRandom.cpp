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
  // else just assign all zeros
  #if defined(A0)
    for (byte i=0; i<byteSize; i++) { analogPins[i]=(byte)A0; }
  #else
    for (byte i=0; i<byteSize; i++) { analogPins[i]=0; }
  #endif



  //== Initialise RAM ==//
  #if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__)
    // 512 bytes
    ramStart = (byte*)0x0100;
    ramEnd = (byte*)0x02FF;
  #elif defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__)
    // 1024 bytes
    ramStart = (byte*)0x0100;
    ramEnd = (byte*)0x4FF;
  #elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__)
    // 2048 bytes
    ramStart = (byte*)0x0100;
    ramEnd = (byte*)0x08FF;
  #elif defined(__AVR_ATmega16U4__)
    // 1280 byes
    ramStart = (byte*)0x0100;
    ramEnd = (byte*)0x05FF;
  #elif defined(__AVR_ATmega32U4__)
    // 2560 bytes
    ramStart = (byte*)0x0100;
    ramEnd = (byte*)0x0AFF;
  #elif defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
    // 8192 bytes
    ramStart = (byte*)0x200;
    ramEnd = (byte*)0x21FF;
  #elif defined(__AVR_ATtiny3224__) || defined(__AVR_ATtiny3226__) || defined(__AVR_ATtiny3227__)
    // 3072 bytes
    ramStart = (byte*)0x3400;
    ramEnd = (byte*)0x3FFF;
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
  #if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) || \
      defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) || \
      defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || \
      defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__) || \
      defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__) || \
      defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || \
      defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
    timerACountAddress = (byte*)0x46; //8 bit Timer 0
    timerBCountAddress = (byte*)0x84; // 16 bit Timer 1

    byte* timerAControlAddress = (byte*)0x45; 
    byte* timerBControlAddress = (byte*)0x81; 

    // If clock A is off (no clock), turn on with /1024 prescaling
    if ( (*timerAControlAddress & 0b00000111) == 0)
      *timerAControlAddress |= 0b00000101; 
    
    // If clock A is off (no clock source), turn on with no prescaling
    if ( (*timerBControlAddress & 0b00000111) == 0)
      *timerBControlAddress |= 0b00000001; 


  #elif defined(__AVR_ATtiny3224__) || defined(__AVR_ATtiny3226__) || defined(__AVR_ATtiny3227__)
    timerACountAddress = (byte*)0xA20; // 0x0A00 + 0x20 Timer A0
    timerBCountAddress = (byte*)0xA8A; // 0x0A80 + 0x0A Timer B0

    byte* timerAControlAddress = (byte*)0x0A00; 
    byte* timerBControlAddress = (byte*)0x0A80; 

    // If clock A is disabled, enable with /1024 prescaling
    if ( (*timerAControlAddress & 0b00000001) == 0)
      *timerAControlAddress |= 0b00001111; 
    
    // If clock A is disabled, enable with no prescaling
    if ( (*timerBControlAddress & 0b00000001) == 0)
      *timerBControlAddress |= 0b00000001; 


  #else
    // Else we have no idea and users should set the address manually so we disable ranclock first
    timerACountAddress = (byte*)0x0;
    timerBCountAddressB = (byte*)0x0;
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
  
  {
  if (flags.enableRamdom)
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

byte AlmostRandom::getLastRunCode()
{
  return flags.runCode;
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
  



