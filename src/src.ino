#include "AlmostRandom.h"

AlmostRandom ar;
byte pins[8] = {A0,A1,A2,A3,A4,A5,A0,A1};

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

  pressEnter('s', randomTest);  


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

void randomTest()
{
  unsigned int loops = 10000;
  ar.setRanalog (pins);

  Serial.println("Ranalog: ");
  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRanalog());
  Serial.println();
  
  Serial.println("Ramdom: ");
  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRamdom());
  Serial.println();

  Serial.println("Ranclock: ");
  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRanclock());
  Serial.println();

  Serial.println("Rainput: ");
  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRainput());
  Serial.println();

  Serial.println("AlmostRandom: ");
  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRandomByte());
  Serial.println();


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
