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

// Example: TOTO & 4D
// TOTO is a game in Singapore where you pick 6 unique numbers from 1 to 49.
// 4D is a game in Singapore were you pick a number from 0000 to 9999.
// This example shows you how to use AmostRandom to generate playing numbers for the games.  

#include <AlmostRandom.h>
#include <InsertionSort.h>

// Create an instant of AlmostRandom
AlmostRandom ar;

// Define the number or digit count and array to store them
const byte TOTO_NUM_CNT = 6;
const byte FD_NUM_CNT = 4;
byte TOTO[TOTO_NUM_CNT];
byte FD[FD_NUM_CNT];


void setup()
{
  Serial.begin(9600);
  
  // Pause until something is entered into Serial monitor
  while(Serial.available()==0){}

  // Clear Serial buffer
  clearSerial(); 

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
  // Print menu
  Serial.println("Generate playing numbers for:");
  Serial.println("1. TOTO (6 unique numbers, 1 to 49)");
  Serial.println("2. 4D (1 number from 0000 to 9999)");
  Serial.print("Choice: ");
  
  // Pause until user enters something
  while (Serial.available()==0){}

  // Grab the first character
  char c = Serial.read();

  // Clear the rest of the buffer
  clearSerial();

  // Print the inout
  Serial.print(c);
  Serial.print("\n\n");
  
  // Switch the input character
  switch (c)
  {
    // If 1, generate TOTO
    case '1':
      getTOTO();
      Serial.print("TOTO: ");
      // Use the function in InsertionSort to print the array
      InsertionSort<byte>::printlnArray(TOTO, TOTO_NUM_CNT);
      break;

    // If 2, generate 4D
    case '2':
      getFD();
      Serial.print("4D: ");
      // Use the function in InsertionSort to print the array
      InsertionSort<byte>::printlnArray(FD, FD_NUM_CNT);
      break;

    // Else, the input is invalid
    default:
      Serial.println("Invalid choice.");
      break;     
  } 

  Serial.println("\n----------\n");
}


// Function to get TOTO numbers
void getTOTO()
{
  // Loop for TOTO_NUM_CNT, which is 6, times
  for (byte i=0; i<TOTO_NUM_CNT; i++)
  {
    // Get random byte
    byte rand = ar.getRandomByte();
    // Map the byte to 1 to 49
    rand = map(rand, 0, 255, 1, 49);
    
    // Check from beginning if the number repeats
    for (byte j=0; j<i; j++)
    {
      // Continues if it doesnt repeat
      if (TOTO[j] != rand) continue;

      // Else get a new random number
      rand = ar.getRandomByte();
      rand = map(rand, 0, 255, 1, 49);

      // Reset j to 0 so the loop starts over again to check for repeats
      j=0;
    }

    // Store the TOTO number
    TOTO[i] = rand;
  }

  // Sort the array from small to large number
  InsertionSort<byte>::sort(TOTO, TOTO_NUM_CNT);
}


// Function to get 4D numbers
void getFD()
{
  // Loop for FD_NUM_CNT, which is 4, times
  for (byte i=0; i<FD_NUM_CNT; i++)
  {
    // Get a random byte
    byte rand = ar.getRandomByte();
    // Map to 0 to 9
    FD[i] = map(rand, 0, 255, 0, 9);
  }

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
