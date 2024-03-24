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



#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

template <typename T>
class InsertionSort
{

public:
  /*
    Insertion Sort code generated from chatGPT. 
    chatGPT recommends insertion sort due to its simplicity and relatively small memory footprint.
  */
  static void sort(T arr[], unsigned int size)
  {
      for (unsigned int i = 1; i < size; i++) 
      {
          T key = arr[i];
          int j = i - 1;
          
          // Move elements of arr[0..i-1], that are greater than key, to one position ahead
          // of their current position
          while (j >= 0 && arr[j] > key) 
          {
              arr[j + 1] = arr[j];
              j = j - 1;
          }
          arr[j + 1] = key;
      }
  }



  static void printArray(T arr[], unsigned int size)
  {
    for (unsigned int i=0; i<size; i++)
    {
      Serial.print(arr[i]);
      Serial.print(' ');
    }  
  }



  static void printlnArray(T arr[], unsigned int size)
  {
    printArray(arr, size);
    Serial.println();
  }
};



#endif