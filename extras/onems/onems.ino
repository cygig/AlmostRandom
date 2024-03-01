void setup()
{
  Serial.begin(9600);
  unsigned long start, end;
  unsigned long delayTime = 1;
  unsigned long loops=10000;

  while (Serial.available()==0){}

  for (unsigned long i=0; i<loops; i++)
  {
    start = micros();
    delay(delayTime);
    end = micros();
    Serial.println(end-start);
  }
}


void loop()
{

}

