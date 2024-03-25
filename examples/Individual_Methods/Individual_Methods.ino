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

// Example: Individual Methods
// This example will generate random numbers using each individual methods.

#include <AlmostRandom.h>

// Declare an instance of AlmostRandom
AlmostRandom ar;


void setup()
{
  Serial.begin(9600);
  Serial.println("Press Enter to get a new set of random numbers.");

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
  // Enter something to generate random numbers
  while (Serial.available()==0){}
  // Clear the buffer
  clearSerial();

  // Generate one random byte
  ar.getRandomByte();

  // Print header
  Serial.println("Random Byte");
  Serial.println("----------");

  // Get the Ranalog byte used during getRandomByte()
  Serial.print("Ranalog:\t");
  Serial.print(ar.getLastRanalog());
  Serial.print("\t(0b");
  // Pad zero to eight bits
  Serial.print(AlmostRandom::toBin(ar.getLastRanalog(), 8));
  Serial.println(")");

  // Get the Ramdom byte used during getRandomByte()
  Serial.print("Ramdom:\t\t");
  Serial.print(ar.getLastRamdom());
  Serial.print("\t(0b");
  // Pad zero to eight bits
  Serial.print(AlmostRandom::toBin(ar.getLastRamdom(), 8));
  Serial.println(")");

  // Get the Ranclock byte used during getRandomByte()
  Serial.print("Ranclock:\t");
  Serial.print(ar.getLastRanclock());
  Serial.print("\t(0b");
  // Pad zero to eight bits
  Serial.print(AlmostRandom::toBin(ar.getLastRanclock(), 8));
  Serial.println(")");

  // Get the Rainput byte used during getRandomByte()
  Serial.print("Rainput:\t");
  Serial.print(ar.getLastRainput());
  Serial.print("\t(0b");
  // Pad zero to eight bits
  Serial.print(AlmostRandom::toBin(ar.getLastRainput(), 8));
  Serial.println(")");

  // Get the final byte used during getRandomByte()
  Serial.print("AlmostRandom*:\t");
  Serial.print(ar.getLastRandomByte());
  Serial.print("\t(0b");
  // Pad zero to eight bits
  Serial.print(AlmostRandom::toBin(ar.getLastRandomByte(), 8));
  Serial.println(")\n*All Methods");

  // Get the run code for getRandomByte()
  Serial.print("Run code:\t");
  Serial.print(ar.getLastRunCode());
  Serial.print("\t(0b");
  // Pad zero to four bits
  Serial.print(AlmostRandom::toBin(ar.getLastRunCode(), 4));
  Serial.println(")");

  Serial.println("\n----------");
  Serial.println("Press Enter to get a new set of random numbers.");
  Serial.println("----------\n");

}


// Function to clear Serial buffer
void clearSerial()
{
  // Wait a while for the buffer to fill
  delay(5);

  // Read and thus delete everything while the buffer is not empty
  while(Serial.available()>0)
  {
    Serial.read();
  }
}