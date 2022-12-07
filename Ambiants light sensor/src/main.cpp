

#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"

  /*  https://www.youtube.com/channel/UCr688fGR4aI_tWYD-YKYrzQ
      https://www.youtube.com/channel/UCr688fGR4aI_tWYD-YKYrzQ*/ 


int temt6000Pin = A0;// Analog pin for reading sensor data
float light;
int light_value;

void setup() {
  
  Serial.begin(9600);

  wifiConnect();                 
  MQTTConnect();

  pinMode(temt6000Pin, INPUT); //data pin for ambientlight sensor
  pinMode(13, OUTPUT);

}

void loop() {
  
   light_value = analogRead(temt6000Pin);
  
  light = light_value * 0.0976;// percentage calculation 
  Serial.println(light);
   Serial.println(light_value,DEC);
  delay(300);
  if (light_value >300 && light_value <700) {
    digitalWrite(13, HIGH);
  }else if(light_value >0 && light_value <300) {
  digitalWrite(8, HIGH);
  digitalWrite(13,HIGH);}
  else {digitalWrite(13,LOW);
       digitalWrite(8, LOW);}

 appendPayload("Intensite lumiere",light_value );  //Ajout de la donnée température au message MQTT
  sendPayload();                                  

}   