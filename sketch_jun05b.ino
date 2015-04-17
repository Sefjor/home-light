#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9,10);
int role = 1; // 1=tranciever, 2=reciever

void setup()
{

  Serial.begin(9600);
 Serial.println("BEGINNING");
  
  pinMode(7, OUTPUT); 
  radio.begin();
  if ( role ==  1)//tranciever
  pinMode(6, INPUT);
  radio.openWritingPipe(0xF0F0F0E0E1LL);
  if ( role ==  2) //reciever
   {
     radio.openReadingPipe(1, 0xF0F0F0E0E1LL);
     radio.startListening();
}
}

void loop()
{

   if (role ==  1) //tranciever
 {
   int sensorVal = digitalRead(6);
  Serial.print("Sending ");
  Serial.print(sensorVal);
      bool ok = radio.write(&sensorVal, sizeof(int));
       delay(100);
     if (ok)
    Serial.println("ok");
     else Serial.println("fail");
 }
  if ( role ==  2) //reciever
  {
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      unsigned long got_time;
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &got_time, sizeof(unsigned long) );
//Serial.print("got it: ");
  Serial.println(got_time);
    

        // Delay just a little bit to let the other unit
        // make the transition to receiver
        delay(20);
        
      }
  if (got_time == HIGH)  digitalWrite(7, HIGH);
  
  else digitalWrite(7, LOW);
  
}
  }
}
