#include "AlmostRandom.h"

AlmostRandom ar;

void setup()
{
  Serial.begin(9600);
  ar.setRanalog(2);
  while(Serial.available()==0){}


  unsigned long start, stop;
  unsigned long loops=10000;

  start=millis();
  for (unsigned long i=0; i<loops; i++)
  {
    ar.getRanalog();
  }
  stop=millis();

  Serial.println(stop-start);
}

void loop()
{
  


}