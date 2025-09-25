#include<dht.h>
# define dht_dpin A1
dht DHT;

int ledPin= 13; //the number of LED pin
int fanPin = 12;
int ldrPin =  A0; //the number of LDR pin


void setup(){
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(fanPin,HIGH);
  pinMode(ldrPin,INPUT);
}

void loop(){
  // Code for controlling light intensity
  int ldrStatus = analogread(ldrPin);
  float volt=(value/1023.0)*5;
  float lux=((2500/volt)-500)/3.3;
  if (lux<100){
    Serial.println("Insufficiency of light, LED is ON");
    delay(100);
    digitalWrite(ledPin, HIGH);

  }
  else{
    Serial.println("Sufficiency of light, LED is OFF");
    delay(100);
    digitalWrite(ledPin, LOW);
  }


  //code for controlling humidity
  DHT.read11(dht_dpin);
  Serial.print(" humidity= ");
  float humidity = DHT.humidity;
  Serial.print(humidity);
  Serial.println(" % ");
  
  //code for controlling temperature
  Serial.print(" temperature = ");
  float temperature = DHT.temperature;
  Serial.print(temperature);
  Serial.println(" degree celsius ");
  if (temperature>35){
    Serial.println("Very high temperature, needs to cool down");
    delay(100);
    digitalWrite(fanPin, HIGH);

  }
  else if(temperature<25) {
    Serial.println("Low temperature");
    delay(100);
    digitalWrite(nichromePin, HIGH);
  }
  else{
    Serial.println("Optimum temperature");
  }


 




  
  
}
