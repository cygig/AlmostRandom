#include "AlmostRandom.h"

AlmostRandom ar;
byte pins[8] = {1,2,3,6,7,8,9,10};

void setup()
{
  Serial.begin(9600);
  while(Serial.available()==0){}

  // unsigned long start, stop;
  // unsigned long loops=10000;
  
  ar.setRanalog(pins);

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

  pressEnter('s', timeTest);  


}

void pressEnter(char match, void (*myFunc)())
{
  //void (*callBackFunction)() = myFunc;
  if (Serial.available()>0)
  {
    char read = Serial.read();

    Serial.print("Iput detected: ");

    if (read<=32)
      Serial.println((byte)read);
    else
      Serial.println(read);

    //  We ignore the input chat if it is \n, for PUTTY
    if (read==match || read=='\n')
    {
      Serial.println("Executing...");
      myFunc();
    }

    delay(10); // Wait for data to arrive at the Serial buffer
    while (Serial.available()>0) Serial.read(); // Flush Serial

  }
  
}



void timeTest()
{
  unsigned long loops = 10000;
  unsigned long start, stop;

  start = millis();
  for (unsigned int i=0; i<loops; i++)
  {
    ar.getRanalog();
  }
  stop = millis();

  Serial.print("Ranalog Time: ");
  Serial.println(stop-start);

  
  start = millis();
  for (unsigned int i=0; i<loops; i++)
  {
    ar.getRamdom();
  }
  stop = millis();

  Serial.print("Ramdom Time: ");
  Serial.println(stop-start);


  
  start = millis();
  for (unsigned int i=0; i<loops; i++)
  {
    ar.getRanclock();
  }
  stop = millis();

  Serial.print("Ranclock Time: ");
  Serial.println(stop-start);


  
  start = millis();
  for (unsigned int i=0; i<loops; i++)
  {
    ar.getRainput();
  }
  stop = millis();

  Serial.print("Rainput Time: ");
  Serial.println(stop-start);



  start = millis();
  for (unsigned int i=0; i<loops; i++)
  {
    ar.getRandomByte();
  }
  stop = millis();

  Serial.print("AlmostRandom Time: ");
  Serial.println(stop-start);
}
