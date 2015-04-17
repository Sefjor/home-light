#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9,10);
int role = 2; // 1=tranciever, 2=reciever
int val = 3;

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
     radio.openReadingPipe(1,0xF0F0F0E0E1LL);
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
      if (ok)
      Serial.println("ok");
      else Serial.println("fail");
      delay(20);
 }
  if ( role ==  2) //reciever
  {
 //   if ( radio.available() )
  //  {
      int got_time;
        if (radio.read( &got_time, sizeof(int))) {
        delay(80);
Serial.print("got it: "); Serial.println(got_time); 
if (val != got_time) {
  val = got_time;
if (val > 0)  digitalWrite(7, HIGH);
  
 else digitalWrite(7, LOW);
 }
        }
     // }

}
}
