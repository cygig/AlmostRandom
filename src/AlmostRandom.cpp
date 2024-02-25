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
  flags.enableRainput = false;
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
    timerBCountAddressB = (byte*)0x84; // 16 bit Timer 1

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
  



