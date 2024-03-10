#include "AlmostRandom.h"

AlmostRandom ar;
byte analogPin = 2;

void setup()
{
  Serial.begin(9600);
  while(Serial.available()==0){}
  Serial.println("Begin!");

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
    while (Serial.available()>0) Serial.read();
  }
  
}


void randomTest()
{
  unsigned int loops = 10000;
  ar.setRanalog(analogPin);

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

  Serial.print("Run Code: ");
  Serial.println(ar.getLastRunCode(), BIN);

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



