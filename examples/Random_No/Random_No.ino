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

// Example: Random No
// This example will print different kinds of random numbers supported by this library every five seconds to the Serial monitor.

#include <AlmostRandom.h>
#include <InsertionSort.h>

// Create an instance of AlmostRandom
AlmostRandom ar;

// Array to hold the random bytes
const byte arraySize = 6;
byte byteArray[arraySize];

void setup()
{
  Serial.begin(9600);

  // Sketch will only start after you enter something on the Serial monitor
  while (Serial.available()==0){}

  // You will need to enable the timers for ESP32-S3
  #if defined(CONFIG_IDF_TARGET_ESP32S3)
    // Start ESP32S3's timer
    uint32_t* G0T0_CTRL = (uint32_t*)0x6001F000;
    uint32_t* G1T0_CTRL = (uint32_t*)0x60020000;

    *G0T0_CTRL |= (1<<31);
    *G1T0_CTRL |= (1<<31);
  #endif

}

void loop()
{
  // Get random byte
  byte rByte = ar.getRandomByte();
  // Print to Serial
  Serial.print("Random byte:\t\t\t");
  Serial.print(rByte);
  Serial.print("\t\t(0b");
  Serial.print(AlmostRandom::toBin(rByte,8));
  Serial.println(")");


  // Get random signed integer
  int rInt = ar.getRandomInt();
  // Print to Serial
  Serial.print("Random integer:\t\t\t");
  Serial.print(rInt);
  Serial.print("\t\t(0b");
  Serial.print(AlmostRandom::toBin(rInt,16));
  Serial.println(")");


  // Get random unsigned integer
  unsigned int rUInt = ar.getRandomUInt();
  // Print to Serial
  Serial.print("Random unsigned integer:\t");
  Serial.print(rUInt);
  Serial.print("\t\t(0b");
  Serial.print(AlmostRandom::toBin(rUInt,16));
  Serial.println(")");


  // Get random signed long
  long rLong = ar.getRandomLong();
  // Print to Serial
  Serial.print("Random long:\t\t\t");
  Serial.print(rLong);
  Serial.print("\t(0b");
  Serial.print(AlmostRandom::toBin(rLong,32));
  Serial.println(")");


  // Get random unsigned long
  unsigned long rULong = ar.getRandomULong();
  // Print to Serial
  Serial.print("Random unsigned long:\t\t");
  Serial.print(rULong);
  Serial.print("\t(0b");
  Serial.print(AlmostRandom::toBin(rULong,32));
  Serial.println(")");


  // Get random float
  float rFloat = ar.getRandomFloat();
  // Print to Serial
  Serial.print("Random float:\t\t\t");
  Serial.print(rFloat, 3);
  Serial.print("\t\t(0b");
  Serial.print(rFloat, BIN);
  Serial.println("), this will not print properly");


  // Get 6 random byte
  for (byte i=0; i<arraySize; i++)
  {
    byteArray[i] = ar.getRandomByte();
  }
  // Print to Serial
  Serial.print("Random Byte Array (Unsorted, non-unique, unmapped):\t");
  InsertionSort<byte>::printlnArray(byteArray, arraySize);


  // Get 6 random byte
  for (byte i=0; i<arraySize; i++)
  {
    byteArray[i] = ar.getRandomByte();
  }
  // Sort them
  InsertionSort<byte>::sort(byteArray, arraySize); 
  // Print to Serial
  Serial.print("Random Byte Array (Sorted, non-unique, unmapped)\t");
  InsertionSort<byte>::printlnArray(byteArray, arraySize);


  // Get 6 unique random byte
  for (byte i=0; i<arraySize; i++)
  {
    byte temp = ar.getRandomByte();

    // Check for matches in the previous generations
    for (byte j=0; j<i; j++)
    {
      // Skip to the next loop if numbers are different
      if (byteArray[j]!=temp) continue;

      // Else generate temp again and reset the loop
      temp = ar.getRandomByte();
      j=0;
    }
    byteArray[i]=temp;
  }
  // Sort them
  InsertionSort<byte>::sort(byteArray, arraySize);
  // Print to Serial
  Serial.print("Random Byte Array (Sorted, unique, unmapped):\t\t");
  InsertionSort<byte>::printlnArray(byteArray, arraySize);


  // Get 6 unique random byte
  for (byte i=0; i<arraySize; i++)
  {
    byte temp = ar.getRandomByte();
    
    // Map from 0 to 255 to 1 to 49
    temp = (byte)map(temp, 0, 255, 1, 49);

    // Check for matches in the previous generations
    for (byte j=0; j<i; j++)
    {
      // Skip to the next loop if numbers are different
      if (byteArray[j]!=temp) continue;

      // Else generate temp again and reset the loop
      temp = ar.getRandomByte();
      temp = (byte)map(temp, 0, 255, 1, 49);
      j=0;
    }
    byteArray[i]=temp;
  }
  // Sort them
  InsertionSort<byte>::sort(byteArray, arraySize);
  // Print to Serial
  Serial.print("Random Byte Array (Sorted, unique, mapped):\t\t");
  InsertionSort<byte>::printlnArray(byteArray, arraySize);


  Serial.println("----------");


  // Wait 5s
  delay(5000);

}



