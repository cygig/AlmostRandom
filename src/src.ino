#include "AlmostRandom.h"
#include "InsertionSort.h"

AlmostRandom ar;
const byte arraySize = 6;
byte byteArray[arraySize];

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
  byte rByte = ar.getRandomByte();
  Serial.print("Random byte:\t\t\t");
  Serial.print(rByte);
  Serial.print("\t\t(0b");
  Serial.print(AlmostRandom::toBin(rByte,8));
  Serial.println(")");


  int rInt = ar.getRandomInt();
  Serial.print("Random integer:\t\t\t");
  Serial.print(rInt);
  Serial.print("\t\t(0b");
  Serial.print(AlmostRandom::toBin(rInt,16));
  Serial.println(")");


  unsigned int rUInt = ar.getRandomUInt();
  Serial.print("Random unsigned integer:\t");
  Serial.print(rUInt);
  Serial.print("\t\t(0b");
  Serial.print(AlmostRandom::toBin(rUInt,16));
  Serial.println(")");


  long rLong = ar.getRandomLong();
  Serial.print("Random long:\t\t\t");
  Serial.print(rLong);
  Serial.print("\t(0b");
  Serial.print(AlmostRandom::toBin(rLong,32));
  Serial.println(")");


  unsigned long rULong = ar.getRandomULong();
  Serial.print("Random unsigned long:\t\t");
  Serial.print(rULong);
  Serial.print("\t(0b");
  Serial.print(AlmostRandom::toBin(rULong,32));
  Serial.println(")");


  float rFloat = ar.getRandomFloat();
  Serial.print("Random float:\t\t\t");
  Serial.print(rFloat);
  Serial.print("\t\t(0b");
  Serial.print(rFloat, BIN);
  Serial.println("), this will not print properly");


  for (byte i=0; i<arraySize; i++)
  {
    byteArray[i] = ar.getRandomByte();
  }
  Serial.print("Random Byte Array (Unsorted, non-unique, unmapped):\t");
  InsertionSort<byte>::printlnArray(byteArray, arraySize);


  for (byte i=0; i<arraySize; i++)
  {
    byteArray[i] = ar.getRandomByte();
  }
  InsertionSort<byte>::sort(byteArray, arraySize);
  Serial.print("Random Byte Array (Sorted, non-unique, unmapped)\t");
  InsertionSort<byte>::printlnArray(byteArray, arraySize);


  for (byte i=0; i<arraySize; i++)
  {
    byte temp = ar.getRandomByte();
    for (byte j=0; j<i; j++)
    {
      if (byteArray[j]!=temp) continue;

      temp = ar.getRandomByte();
      j=0;
    }
    byteArray[i]=temp;
  }
  InsertionSort<byte>::sort(byteArray, arraySize);
  Serial.print("Random Byte Array (Sorted, unique, unmapped):\t\t");
  InsertionSort<byte>::printlnArray(byteArray, arraySize);


  for (byte i=0; i<arraySize; i++)
  {
    byte temp = ar.getRandomByte();
    temp = (byte)map(temp, 0, 255, 1, 49);

    for (byte j=0; j<i; j++)
    {
      if (byteArray[j]!=temp) continue;

      temp = ar.getRandomByte();
      temp = (byte)map(temp, 0, 255, 1, 49);
      j=0;
    }
    byteArray[i]=temp;
  }
  InsertionSort<byte>::sort(byteArray, arraySize);
  Serial.print("Random Byte Array (Sorted, unique, mapped):\t\t");
  InsertionSort<byte>::printlnArray(byteArray, arraySize);


  Serial.println("----------");

  delay(5000);


}



