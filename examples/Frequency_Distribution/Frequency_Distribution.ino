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

// Example: Frequency Distribution
// This example will generate a report to show the frequency distribution of the random bytes

#include "C:\Users\cygig\Desktop\AlmostRandom\src\AlmostRandom.h"
#include "C:\Users\cygig\Desktop\AlmostRandom\src\AlmostRandom_ranalog.cpp"
#include "C:\Users\cygig\Desktop\AlmostRandom\src\AlmostRandom_ramdom.cpp"
#include "C:\Users\cygig\Desktop\AlmostRandom\src\AlmostRandom_ranclock.cpp"
#include "C:\Users\cygig\Desktop\AlmostRandom\src\AlmostRandom_rainput.cpp"
#include "C:\Users\cygig\Desktop\AlmostRandom\src\AlmostRandom.cpp"

// Declare an instance of AlmostRandom
AlmostRandom ar;

// How many random numbers to generate
const unsigned int loops=10000;

// Max of 256 values (0-255) in a byte
const int byteMax = 256;

// Store the statistics
// One byte can store 255, if the results are truly random, each value should occur
// 10,000/256 = 39 times. Anything more than 255 will be way too much.
byte stats[byteMax];


// Prompt to ask users to press Enter
const char prompt[]="Press Enter to test random numbers and generate reports.";

// Define rows and columns to print report
const byte textCol=8;


void setup()
{
  Serial.begin(9600);
  Serial.println(prompt);

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
  while(Serial.available()==0){}
  
  Serial.print("Generating ");
  Serial.print(loops); 
  Serial.println(" random numbers...\n");

  generateRandomNo();

  Serial.println("Text Report (Possible Value: Frequency)\n---------------------------------------");
  drawTextReport();

  Serial.println("\nFrequency Graph\n---------------");
  drawGraph(0, 127, 24);

  clearSerial();
}


void generateRandomNo()
{
  // zero all values
  for (int i=0; i<byteMax; i++)
    stats[i] = 0;

  // Generate 10,000 random numbers
  for (unsigned int i=0; i<loops; i++)
  {
    byte temp = ar.getRandomByte();
    // If the frequency is already 255, remain at 255
    if (stats[temp]==byteMax-1) continue;

    // Else increase frequency by one
    else stats[temp]++;
  }
}


void drawTextReport()
{
  // Print frequencies of all byte values
  for (int i=0; i<byteMax; i++)
  {
    // if byte value is less than 10, pad two zeros
    if(i<10)
      Serial.print("00");
    // else if byte value is less than 100, pad one zero
    else if (i<100)
      Serial.print("0");
    
    // Print byte value
    Serial.print(i);
    Serial.print(": ");
    // Print frequency
    Serial.print(stats[i]);

    // If frequency is 255, add a '+' size
    if (stats[i]==255)
      Serial.print("+");

    // New line after eight byte values, else print tabs
    if ( i%textCol == (textCol-1) )
      Serial.println();
    else
      Serial.print("\t\t");
  }
}


void drawGraph(int rangeLow, int rangeHigh, byte row)
{
  for (int i=rangeLow; i<=rangeHigh; i++)
  {
    byte temp = stats[i];
    temp = map(temp, 0, byteMax-1, 0, row-1); 
    temp = row-1-temp;
    stats[i] = temp;  
  }


  for (byte i=0; i<row; i++)
  {
    if (i==0) Serial.print("255");
    else if (i==(row/2)) Serial.print("128");
    else if (i==(row-1)) Serial.print("  0");
    else Serial.print("   ");

    Serial.print("|");

    for (int j=rangeLow; j<=rangeHigh; j++)
    {
      if(stats[j]==i) Serial.print("*");
      else if (i==row-1) Serial.print("-");
      else Serial.print(" ");
    }
    Serial.println();
  }

  const byte interval=16;
  byte count=0;
  Serial.print("    ");
  for (int j=rangeLow; j<=rangeHigh; j++)
  {
    if (count%interval==0)
    {
      Serial.print(j);
      if (j<10) j+=1;
      else if (j<100) j+=2;
      count=0;
    }
    else Serial.print(" ");
    count++;

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