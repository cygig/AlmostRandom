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