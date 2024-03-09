#include "AlmostRandom.h"

AlmostRandom ar;
byte analogPin = A0;

void setup()
{
  Serial.begin(9600);
  while(Serial.available()==0){}
  Serial.println("Begin!");

  uint32_t* G0T0_CTRL = (uint32_t*)0x6001F000;
  uint32_t* G1T0_CTRL = (uint32_t*)0x60020000;
  *G0T0_CTRL |= (1<<31);
  *G1T0_CTRL |= (1<<31);
}

void loop()
{
  pressEnter('s', getRanclock);  
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

void getAnalogCheck()
{

  byte pin[]={15, 16, 17, 18, 15, 16, 17, 18};
  ar.setRanalog(pin);

}

void getAnalogRead()
{
  unsigned int loops = 10000;
  Serial.println("analogRead: ");

  for (unsigned int i=0; i<loops; i++)
    Serial.println(analogRead(analogPin));

}


void getRanalog()
{
  byte pin[]={A0, A1, A2, A3, A4, A5, A0, A1};
  unsigned int loops = 10000;
  ar.setRanalog(pin);
  Serial.println("Ranalog: ");

  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRanalog());

}

void getRamdom()
{
  ar.setRamdom((byte*)0x3FC88000, (byte*)0x3FCFFFFF);
  ar.enableRamdom(true);
  unsigned int loops = 10000;
  Serial.println("Ramdom: ");

  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRamdom());

}

void getRanclock()
{
  unsigned int loops = 5;
  Serial.println("Ranclock: ");

  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRanclock());

}



void getRainput()
{
  unsigned int loops = 10000;
  Serial.println("Rainput: ");

  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRainput());
}

void getAlmostRandom()
{
  //byte pin[]={A0, A1, A2, A3, A4, A5, A0, A1};
  unsigned int loops = 10000;
  ar.setRanalog(analogPin);
  Serial.println("AlmostRandom: ");

  for (unsigned int i=0; i<loops; i++)
    Serial.println(ar.getRandomByte());
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



/*
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
  #elif defined(CONFIG_IDF_TARGET_ESP32S3)
    Serial.println("ESP32S3");
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

  #elif defined (CONFIG_IDF_TARGET_ESP32S3)

    uint32_t* G0T0_CTRL = (uint32_t*)0x6001F000;
    uint32_t* G0T0_LO = (uint32_t*)0x6001F004;
    uint32_t* G0T0_HI = (uint32_t*)0x6001F008;
    uint32_t* G0T0_UPDATE = (uint32_t*)0x6001F00C;

    uint32_t* G0T1_CTRL = (uint32_t*)0x6001F024;
    uint32_t* G0T1_LO = (uint32_t*)0x6001F028;
    uint32_t* G0T1_HI = (uint32_t*)0x6001F02C;
    uint32_t* G0T1_UPDATE = (uint32_t*)0x6001F030;

    uint32_t* G1T0_CTRL = (uint32_t*)0x60020000;
    uint32_t* G1T0_LO = (uint32_t*)0x60020004;
    uint32_t* G1T0_HI = (uint32_t*)0x60020008;
    uint32_t* G1T0_UPDATE = (uint32_t*)0x6002000C;

    uint32_t* G1T1_CTRL = (uint32_t*)0x60020024;
    uint32_t* G1T1_LO = (uint32_t*)0x60020028;
    uint32_t* G1T1_HI = (uint32_t*)0x6002002C;
    uint32_t* G1T1_UPDATE = (uint32_t*)0x60020030;

    
    Serial.print("Timer G0 T0 Control: ");
    Serial.println(*G0T0_CTRL, BIN);
    *G0T0_CTRL |= (1<<31);
    //*G0T0_UPDATE = (1<<31);
    Serial.print("Latch: ");
    Serial.print(*G0T0_UPDATE, BIN);
    Serial.print("\tCount: ");
    Serial.print(*G0T0_HI, BIN);
    Serial.print(" ");
    Serial.println(*G0T0_LO, BIN);

    
    Serial.print("Timer G0 T1 Control: ");
    Serial.println(*G0T1_CTRL, BIN);
    *G0T1_CTRL |= (1<<31);
    //*G0T1_UPDATE = (1<<31);
    Serial.print("Latch: ");
    Serial.print(*G0T1_UPDATE, BIN);
    Serial.print("\tCount: ");
    Serial.print(*G0T1_HI, BIN);
    Serial.print(" ");
    Serial.println(*G0T1_LO, BIN);

    
    
    Serial.print("Timer G1 T0 Control: ");
    Serial.println(*G1T0_CTRL, BIN);
    *G1T0_CTRL |= (1<<31);
    //*G1T0_UPDATE = (1<<31);
    Serial.print("Latch: ");
    Serial.print(*G1T0_UPDATE, BIN);
    Serial.print("\tCount: ");
    Serial.print(*G1T0_HI, BIN);
    Serial.print(" ");
    Serial.println(*G1T0_LO, BIN);

    
    Serial.print("Timer G1 T1 Control: ");
    Serial.println(*G1T1_CTRL, BIN);
    *G1T1_CTRL |= (1<<31);
    //*G1T1_UPDATE = (1<<31);
    Serial.print("Latch: ");
    Serial.print(*G1T1_UPDATE, BIN);
    Serial.print("\tCount: ");
    Serial.print(*G1T1_HI, BIN);
    Serial.print(" ");
    Serial.println(*G1T1_LO, BIN);

    Serial.println("----------");
  #endif
}
*/


