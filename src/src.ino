#include "AlmostRandom.h"
#include "InsertionSort.h"

AlmostRandom ar;
const byte size=20;
byte randomArr[size];


void setup()
{
  Serial.begin(9600);

  while (Serial.available()==0){}


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
  Serial.print("Original Array: ");
  for (byte i=0; i<size; i++)
  {
    randomArr[i] = ar.getRandomByte();
  }
  InsertionSort<byte>::printlnArray(randomArr, size);

  Serial.print("Sorted Array: ");
  InsertionSort<byte>::sort(randomArr, size);
  InsertionSort<byte>::printlnArray(randomArr, size);

  Serial.println("----------");

  delay(5000);

}



