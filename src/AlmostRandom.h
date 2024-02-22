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

    byte setRanalog(unsigned int pin);
    byte getRanalog();

    byte setRamdon(byte* ramStart, byte* ramEnd);
    byte getRamdom();

    byte setRanclock(byte* clockAddressA, byte* clockAddressB);
    byte getRanclock();
    

  private: 
     byte randomNumber;


};

#endif
