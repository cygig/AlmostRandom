 const unsigned long loops=10000;
 const unsigned long seed=62353535;

void setup()
{
  Serial.begin(9600);
  randomSeed(seed);

  // Wait for Serial
  while(Serial.available()==0){}
  
 
  Serial.print("Generating ");
  Serial.print(loops);
  Serial.print(" random numbers with seed ");
  Serial.print(seed);
  Serial.println(": ");
  
  for (unsigned long i=0; i<loops; i++)
  {
    Serial.println(random(0,256));
  }
}

void loop()
{

}