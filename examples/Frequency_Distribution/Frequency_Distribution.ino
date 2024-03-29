/*
AlmostRandom generates random number from a few entropy sources within the Arduino.
Copyright (C) 2024 cygigc:\Users\cygig\Desktop\AlmostRandom\src\AlmostRandom.cpp

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; 
either version 2.1 of the License, or (at your option) any c:\Users\cygig\Documents\Arduino\libraries\AlmostRandom\src\AlmostRandom.cpplater version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
c:\Users\cygig\Documents\Arduino\libraries\AlmostRandom\src\AlmostRandom.cpp
You should have received a copy of the GNU Lesser General Public License along with this library; 
if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

// Example: Frequency Distribution
// This example will generate a report to show the frequency distribution of the random bytes in both text and graph form. 

#include <AlmostRandom.h>

// Declare an instance of AlmostRandom
AlmostRandom ar;

// How many random numbers to generate
const unsigned int loops = 10000;

// Max of 256 values (0-255) in a byte
const int byteMax = 256;

// Store the statistics
// One byte can store 255, if the results are truly random, each value should occur
// 10,000/256 = 39 times. Anything more than 255 will be way too much.
byte stats[byteMax];

void setup()
{
  Serial.begin(9600);

  // User need to press Enter to start the random number generation
  promptUser();

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
  // Wait for user to press Enter
  while(Serial.available() == 0){}
  
  // Generate and store the random numbers
  generateRandomNo();

  // Generate the text report
  Serial.println(F("\nText Report (Possible Value: Frequency)\n---------------------------------------"));
  drawTextReport(8); // 8 means 8 columns per row

  // Generate the graphic report
  // We split into two graphs due to the limited details of ASCII characters
  // and the lack of space on Serial monitor
  Serial.println(F("\nFrequency Graph\n---------------"));
  drawGraph(0, 127, 32, 16); // Draw for data 0 to 127, 32 rows, and display the X axis labels at an intervalof 16 values
  drawGraph(128, 255, 32, 16); // Draw for data 128 to 255, 32 rows, and display the X axis labels at an intervalof 16 values

  Serial.println();
  promptUser(); // User need to press Enter to start the random number generation
  clearSerial(); // Clear Serial buffer
}



// Generate loops number of random numbers, store the frequency into array and time
void generateRandomNo()
{
  // Variable to update the serial monitor
  const byte segment = 20; // The Serial monitor will update this amount of times
  const unsigned int chunk = loops / segment; // Count will restart once it hits this amount 
  unsigned int count = 1; // this needs to start from one.

  // Variables to keep time
  // Since Serial.print() can take quite some time, we can remove them from the tally, 
  // we'll call this break time and measured in microseconds
  unsigned long timeStart, timeEnd, timeTotal, breakStart, breakEnd, breakTotal=0;
  double timePerLoop; // double same as float for AVR Arduino, but ESP32-S3 will be able to use

  Serial.print(F("Generating "));
  Serial.print(loops); 
  Serial.print(F(" random numbers, this will take a while: "));

  // zero all values
  for (int i=0; i<byteMax; i++)
    stats[i] = 0;

  timeStart = millis();
  // Generate 10,000 random numbers
  for (unsigned int i=0; i<loops; i++)
  {
    
    byte temp = ar.getRandomByte();

    // If the frequency is already 255, remain at 255
    if ( stats[temp] == ( byteMax - 1 ) ) continue;
    // Else increase frequency by one
    else stats[temp]++;

    // Start timing Serial.print()
    breakStart = micros();

    if (count % chunk == 0)
    {
      Serial.print(F("#"));
      count = 1;
    }
    else count++;

    // End and add to total break time.
    breakEnd = micros();
    breakTotal += (breakEnd - breakStart);
  }

  // End timer and calculate time
  timeEnd = millis();
  timeTotal = timeEnd - timeStart - (breakTotal / 1000);
  timePerLoop = (double)timeTotal / (double)loops;

  Serial.println();

  // Print time taken
  Serial.print(F("Total Time: "));
  Serial.print(timeTotal);
  Serial.print(F(" millisec, excluding "));
  Serial.print(breakTotal);
  Serial.println(F(" microsec of Serial.print() time."));
  Serial.print(F("Time per loop: "));
  Serial.print(timePerLoop, 3);
  Serial.println(F(" millisec."));
}



// Draw text report to Serial
void drawTextReport(byte textCol)
{
  // You cannot have zero columns
  if (textCol == 0) textCol = 1;

  byte count = 1; // This must be 1, not 0, to work.

  // Print frequencies of all byte values
  for (int i=0; i<byteMax; i++)
  {
    // if byte value is less than 10, pad two zeros
    if(i < 10)
      Serial.print(F("00"));
    // else if byte value is less than 100, pad one zero
    else if (i < 100)
      Serial.print(F("0"));
    
    // Print byte value
    Serial.print(i);
    Serial.print(F(": "));
    // Print frequency
    Serial.print(stats[i]);

    // If frequency is 255, add a '+' size
    if (stats[i] == 255) Serial.print(F("+"));

    // New line after eight byte values, else print tabs
    if (count % textCol == 0)
    {
      Serial.println();
      count=1;
    }
    else
    {
      Serial.print(F("\t\t"));
      count++;
    }
    
    
  }
}



// Draw graph to Serial
void drawGraph(unsigned int rangeLow, unsigned int rangeHigh, byte rows, byte xLabelInt)
{
  //== Map the actual values to the scaled one base on row ==//
  for (unsigned int i=rangeLow; i<=rangeHigh; i++)
  {
    byte temp = stats[i];
    temp = map(temp, 0, byteMax-1, 0, rows-1); // Arduino map function
    temp = rows - 1 - temp; // We invert the values as graph is printed top down
    stats[i] = temp;  
  }

  //== Define the positions of the  Y axis labels ==//
  const byte mrk255 = 0;
  const byte mrk191 = (rows / 4) - 1;
  const byte mrk127 = (rows / 2) - 1;
  const byte mrk63  = (rows * 3 / 4) - 1; // Don't involve floats
  const byte mrk0   = rows - 1;

  //== Define the positions of the Y axis title ==//
  const char yTitle[] = "Frequency";
  const byte yTitleLen = strlen(yTitle);
  if ( rows < ( yTitleLen + 2 ) ) rows = yTitleLen + 2; // Increase the rows if not enough
  const byte yTitleStart = (rows - yTitleLen) / 2; // Centre the title
  const byte yTitleEnd = yTitleStart + yTitleLen - 1; //-1 because you write to yTitleStart itself
  byte yTitleIndex = 0; // Index to keep track of which character of the title to print

  //== Define the positions of the X axis title ==//
  const char xTitle[] = "Possible Values";
  const byte xTitleLen = strlen(xTitle);
  const unsigned int dataRange = rangeHigh - rangeLow + 1; //+1 because need to include rangeHigh
  byte xTitleStart;
  // If the X axis isn't long enough, just print from the start ()
  // We don't want to control the data range here unlike the rows
  if ( dataRange < ( (unsigned int)xTitleLen + 2 ) ) xTitleStart = 0; 
  else xTitleStart = (dataRange - xTitleLen) / 2; // Else, print in the middle


  //== Loop each row and print the graph ==//
  for (byte i=0; i<rows; i++)
  {
    // Print the Y axis title in between the positions
    if ( i >= yTitleStart && i <= yTitleEnd )
    {
      Serial.print(yTitle[yTitleIndex]);
      Serial.print(F(" "));
      yTitleIndex++;
    }
    else Serial.print(F("  "));

    // Print the Y axis labels
    if (i == mrk255)      Serial.print(F("255"));
    else if (i == mrk191) Serial.print(F("191"));
    else if (i == mrk127) Serial.print(F("127"));
    else if (i == mrk63)  Serial.print(F(" 63"));
    else if (i == mrk0)   Serial.print(F("  0"));
    else                  Serial.print(F("   "));

    // Print the Y axis
    Serial.print(F("|"));

    // Print the data
    for (unsigned int j=rangeLow; j<=rangeHigh; j++)
    {
      // Draw a star if the row number matches the mapped value
      if(i == stats[j]) Serial.print(F(".")); 

      // Else if there is no match and it is the last row, draw X axis
      else if (i == rows - 1) Serial.print(F("-"));

      // Else print white space
      else Serial.print(F(" "));
    }
    Serial.println();
  }


  // Print the X axis labels
  Serial.print(F("      ")); // Spaces to account for Y axis and its labels
  byte count=1; // This must start from 1 to work, not 0
  for (unsigned int j=rangeLow; j<=rangeHigh; j++)
  {
    // Print X axis labels every xLabelInt. 
    if (count % xLabelInt == 0)
    {
        // Print the X axis label
        Serial.print(j);
        // If single digit, reset count to 1
        if (j < 10) { count = 1; } 
        // Else if double digit, we skip one loop so the X axis will not be too long, then reset count to 2
        else if (j < 100) { j += 1; count = 2; } 
        // Else it is triple digit, we skip two loops and reset count to 3
        else { j += 2; count = 3; }
    }

    // Also force it to print the labels for the first and last values.
    else if ( (j == rangeLow ) || (j == rangeHigh) )
    {
        // Print the X axis label
        Serial.print(j);
        // If single digit, increase count by 1
        if (j < 10) { count++; } 
        // Else if double digit, we skip one loop so the X axis will not be too long, then increase count by 2
        else if (j < 100) { j += 1; count += 2; } 
        // Else it is triple digit, we skip two loops and increase count by 3
        else { j += 2; count += 3; }    
    }

    // Else just print white spaces
    else 
    { 
        Serial.print(F(" "));
        count++; 
    }
      
  }
  Serial.println();

  // Print the X axis title
  Serial.print(F("      ")); // Spaces to account for Y axis and its labels
  for (byte i=0; i<xTitleStart; i++) Serial.print(F(" ")); // Print blank spaces to pad the title
  Serial.println(xTitle);

}



// Function to clear Serial buffer
void clearSerial()
{
  // Wait a while for the buffer to fill
  delay(5);

  // Read and thus delete everything while the buffer is not empty
  while(Serial.available() > 0)
  {
    Serial.read();
  }
}



// Prompt the user to press Enter
void promptUser()
{
  Serial.println(F("Press Enter to test random numbers and generate reports."));
}