#include "AlmostRandom.h"

AlmostRandom ar;
byte pins[8] = {1,2,3,4,5,8,9,10};

void setup()
{
  Serial.begin(9600);
  while(Serial.available()==0){}

  // unsigned long start, stop;
  // unsigned long loops=10000;
  
  ar.setRanalog(2);

  /*
  start=millis();
  for (unsigned long i=0; i<loops; i++)
  {
    //ar.getRamdom();
  }
  stop=millis();
  Serial.println(stop-start);
  */
}

void loop()
{

  pressEnter('\n', test);  


}

void pressEnter(char match, void (*myFunc)())
{
  //void (*callBackFunction)() = myFunc;
  if (Serial.available()>0)
  {
    Serial.println("Dirt in Serial");
    char read = Serial.read();
    if (read==match)
    {
      Serial.println("Command recognised!");
      myFunc();
    }
  }

  while (Serial.available()>0)
    Serial.read();
  
}

void test()
{
  unsigned long start, stop;
  start = millis();
  for (unsigned int i=0; i<10000; i++)
    ar.getRamdom();

  stop = millis();
  Serial.println(stop-start);
}
