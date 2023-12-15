#include "thermistor.h"

#define rele 7
#define PH_OFFSET -1.00
#define SensorPin A0

int pinNTC = A2;
float temperatura;
THERMISTOR thermistor(pinNTC, 10000, 3950, 10000);

unsigned long int avgValue;
float b;
int buf[10],temp;

void setup() {
 pinMode(rele,OUTPUT);
 digitalWrite(rele,LOW);
 pinMode(13,OUTPUT);
 Serial.begin(9600);
 Serial.println("Ready");
}

void loop() {
 temperatura = thermistor.read();
 Serial.print("Temperatura: ");
 Serial.print(temperatura);
 Serial.println(" graus");
 Serial.println("");

 for(int i=0;i<10;i++)
 { 
     buf[i]=analogRead(SensorPin);
     delay(10);
 }
 for(int i=0;i<9;i++)
 {
     for(int j=i+1;j<10;j++)
     {
         if(buf[i]>buf[j])
         {
             temp=buf[i];
             buf[i]=buf[j];
             buf[j]=temp;
         }
     }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
     avgValue+=buf[i];
 float phValue=(float)avgValue*5.0/1024/6;
 phValue = 14 - (1.8*phValue);

 phValue = phValue + PH_OFFSET;
 if(phValue >= 7.0) {
  digitalWrite(rele,HIGH);
 } else {
  digitalWrite(rele,LOW);
  delay(1000);
  digitalWrite(rele,HIGH);
 }

 Serial.print("    pH:");
 Serial.print(phValue,2);
 Serial.println(" ");

 digitalWrite(13, HIGH);
 delay(800);
 digitalWrite(13, LOW); 

 delay(1000);
}