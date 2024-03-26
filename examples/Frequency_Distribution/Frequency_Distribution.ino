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
  drawTextReport(8);

  Serial.println("\nFrequency Graph\n---------------");
  drawGraph(0, 127, 24, 16);

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


void drawTextReport(byte textCol)
{
  // You cannot have zero columns
  if (textCol==0) textCol=1;

  byte count=1; // This must be 1, not 0, to work.

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
    if (stats[i]==255) Serial.print("+");

    // New line after eight byte values, else print tabs
    if ( count % textCol == 0 )
    {
      Serial.println();
      count=1;
    }
    else
    {
      Serial.print("\t\t");
      count++;
    }
    
    
  }
}


void drawGraph(unsigned int rangeLow, unsigned int rangeHigh, byte rows, byte xLabelInt)
{
  //== Map the actual values to the scaled one base on row ==//
  for (unsigned int i=rangeLow; i<=rangeHigh; i++)
  {
    byte temp = stats[i];
    temp = map(temp, 0, byteMax-1, 0, rows-1); // Arduino map function
    temp = rows-1-temp; // We invert the values as graph is printed top down
    stats[i] = temp;  
  }

  //== Define the positions of the  Y axis labels ==//
  byte mrk255 = 0;
  byte mrk191 = (rows/4)-1;
  byte mrk127 = (rows/2)-1;
  byte mrk63  = (rows*3/4)-1; // Don't involve floats
  byte mrk0   = rows-1;

  //== Define the positions of the Y axis title ==//
  char yTitle[]="Frequency";
  byte yTitleLen = strlen(yTitle);
  if (rows<yTitleLen+2) rows=yTitleLen+2; // Increase the rows if not enough
  byte yTitleStart = (rows-yTitleLen)/2; // Centre the title
  byte yTitleEnd = yTitleStart + yTitleLen - 1; //-1 because you write to yTitleStart itself
  byte yTitleIndex = 0; // Index to keep track of which character of the title to print

  //== Define the positions of the X axis title ==//
  char xTitle[]="Possible Values";
  byte xTitleLen = strlen(xTitle);
  unsigned int dataRange = rangeHigh - rangeLow + 1; //+1 because need to include rangeHigh
  byte xTitleStart;
  // If the X axis isn't long enough, just print from the start ()
  // We don't want to control the data range here unlike the rows
  if (dataRange<((unsigned int)xTitleLen+2)) xTitleStart=0; 
  else xTitleStart = (dataRange-xTitleLen)/2; // Else, print in the middle


  //== Loop each row and print the graph ==//
  for (byte i=0; i<rows; i++)
  {
    // Print the Y axis title
    if (i>=yTitleStart && i<=yTitleEnd)
    {
      Serial.print(yTitle[yTitleIndex]);
      Serial.print(" ");
      yTitleIndex++;
    }
    else Serial.print("  ");

    // Print the Y axis labels
    if (i == mrk255)
      Serial.print("255");
    else if (i == mrk191)
      Serial.print("191");
    else if (i == mrk127)
      Serial.print("127");
    else if (i == mrk63)
      Serial.print(" 63");
    else if (i == mrk0)
      Serial.print("  0");
    else
      Serial.print("   ");

    // Print the Y axis
    Serial.print("|");

    // Print the data
    for (unsigned int j=rangeLow; j<=rangeHigh; j++)
    {
      // Draw a star if the row number matches the mapped value
      if(i==stats[j]) Serial.print("."); 

      // Else if there is no match and it is the last row, draw X axis
      else if (i==rows-1) Serial.print("-");

      // Else print white space
      else Serial.print(" ");
    }
    Serial.println();
  }


  // Print the X axis labels
  Serial.print("      "); // Spaces to account for Y axis and its labels
  byte count=1; // This must start from 1 to work, not 0
  byte skip=0;
  for (unsigned int j=rangeLow; j<=rangeHigh; j++)
  {
    // Print X axis labels every xLabelInt. 
    if ( count%xLabelInt == 0 )
    {
      // Print the X axis label
      Serial.print(j);
      // Do nothing is label is single digit, rememeber brackets for blank if()
      if (j<10) {} 
      // Else if double digit, we skip one loop so the X axis will not be too long
      else if (j<100) { j+=1; } 
      // Else it is triple digit, we skip two loops
      else { j+=2; }
      // Reset counter
      count=1;
    }
    // Also force it to print the labels for the first and last values.
    else if ((j==rangeLow) || (j==rangeHigh))
    {
      // Print the X axis label
      Serial.print(j);
      // Do nothing is label is single digit, rememeber brackets for blank if()
      if (j<10) {} 
      // Else if double digit, we skip one loop so the X axis will not be too long
      else if (j<100) { j+=1; } 
      // Else it is triple digit, we skip two loops
      else { j+=2; }
      // Increase counter
      count++;      
    }
    else 
    { 
      Serial.print(" ");
      count++; 
    }
      
  }
  Serial.println();

  // Print the X axis title
  Serial.print("      "); // Spaces to account for Y axis and its labels
  for (byte i=0; i<xTitleStart; i++) Serial.print(" "); // Print blank spaces to pad the title
  Serial.println(xTitle);

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