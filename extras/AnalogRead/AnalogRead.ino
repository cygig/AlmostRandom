void setup()
{
  Serial.begin(9600);
  while(Serial.available()==0){}

  unsigned int loops = 10000;
  
  for (unsigned int i=0; i<loops; i++)
    Serial.println(analogRead(A0));
}

void loop()
{

}