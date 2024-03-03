//#include "AlmostRandom.h"

//AlmostRandom ar;
//byte pins[8] = {A0,A1,A2,A3,A4,A5,A0,A1};

void setup()
{
  Serial.begin(9600);
  while(Serial.available()==0){}

  // unsigned long start, stop;
  // unsigned long loops=10000;
  
  //ar.setRanalog(pins);

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

  pressEnter('s', getClockInfo);  


}

void getClockInfo()
{
  #if defined(__AVR_ATmega328P__)
    Serial.println("ATmega328P");
  #elif defined(__AVR_ATmega32U4__)
    Serial.println("ATmega32u4");
  #elif defined(__AVR_ATmega2560__)
    Serial.println("ATmega2560");
  #elif defined(__AVR_ATtiny3224__)
    Serial.println("ATtiny3224");
  #endif




  #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__) || (__AVR_ATmega2560__)
    Serial.print("TCNT0 Control A: ");
    Serial.print(*(byte*)0x44, BIN);
    Serial.print("\tTCNTo Control B: ");
    Serial.print(*(byte*)0x45, BIN);
    Serial.print("\tCount: ");
    Serial.println(*(byte*)0x46, BIN);

    Serial.print("TCNT1 Control A: ");
    Serial.print(*(byte*)0x80, BIN);
    Serial.print("\tTCNT1 Control B: ");
    Serial.print(*(byte*)0x81, BIN);
    Serial.print("\tCount: ");
    Serial.print(*(byte*)0x85, BIN);
    Serial.print(" ");
    Serial.println(*(byte*)0x84, BIN);

    Serial.print("TCNT2 Control A: ");
    Serial.print(*(byte*)0xB0, BIN);
    Serial.print("\tTCNT2 Control B: ");
    Serial.print(*(byte*)0xB1, BIN);
    Serial.print("\tCount: ");
    Serial.println(*(byte*)0xB2, BIN);

  #elif defined(__AVR_ATtiny3224__)
    Serial.print("TCA0 Control: ");
    Serial.print(*(byte*)0xA00, BIN);
    Serial.print("\tCount: ");
    Serial.print(*(byte*)0xA21, BIN);
    Serial.print(" ");
    Serial.println(*(byte*)0xA20, BIN);

    Serial.print("TCB0 Control: ");
    Serial.print(*(byte*)0xA80, BIN);
    Serial.print("\t\tCount: ");
    Serial.print(*(byte*)0xA8B, BIN);
    Serial.print(" ");
    Serial.println(*(byte*)0xA8A, BIN);

    Serial.print("TCB1 Control: ");
    Serial.print(*(byte*)0xA90, BIN);
    Serial.print("\tCount: ");
    Serial.print(*(byte*)0xA9B, BIN);
    Serial.print(" ");
    Serial.println(*(byte*)0xA9A, BIN);

    Serial.print("RTC Control: ");
    Serial.print(*(byte*)0x140, BIN);
    Serial.print("\t\tCount: ");
    Serial.print(*(byte*)0x149, BIN);
    Serial.print(" ");
    Serial.println(*(byte*)0x148, BIN);

    Serial.print("Millis Timer: ");
    Serial.println(MILLIS_TIMER, HEX);
    

  #endif
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

/*
void rainput()
{
  Serial.println(ar.getRainput());
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
*/