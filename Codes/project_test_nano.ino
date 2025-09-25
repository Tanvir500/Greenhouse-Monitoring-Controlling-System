#include <DHT.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LUX A0
#define DHTPIN 2  
#define DHTTYPE DHT22
#define light 10
#define fan 8
#define humidifier 11
#define pump 5
#define soil 12
#define nichrome 7
//#define select_pin 3

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temperature, humidity;
float volt, lux, value;
int checkFan,checkLight,checkPump,checkSpray,checkNichrome;

void setup() {
  pinMode(soil, INPUT);
  pinMode(LUX,INPUT);
  //pinMode(select_pin,INPUT);
  pinMode(light, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(humidifier, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(nichrome, OUTPUT);
  
  Serial.begin(9600);
  //lcd.backlight();
  lcd.begin();
  lcd.setCursor(0,0);
  dht.begin();
}

void loop() {
  //sensing temperature 
   
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Auto Mode ON");
    delay(1000);
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    if (temperature>20){
    digitalWrite(fan,HIGH);
    checkFan = 1;
    }
    else {
    digitalWrite(fan,LOW);
    checkFan = 0;
    }
    if (temperature<20){
    digitalWrite(nichrome,HIGH);
    checkNichrome = 1;
  }
  else {
    digitalWrite(nichrome,LOW);
    checkNichrome = 0;
  }
  if (humidity<80){
    digitalWrite(humidifier,HIGH);
    checkSpray = 1;
  }
  else {
    digitalWrite(humidifier,LOW);
    checkSpray = 0;
  }
  if(digitalRead(soil)==1){
    digitalWrite(pump,HIGH);
    checkPump = 1;
  }
  else{
    digitalWrite(pump,LOW);
    checkPump = 0;
  }
  value=analogRead(LUX);
  volt=(value/1023.0)*5;
  lux=((2500/volt)-500)/3.3;
  if(lux<10){
    digitalWrite(light,HIGH);
    checkLight = 1;
  }
  else{
    digitalWrite(light,LOW);
    checkLight = 0;
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  if (checkFan==1){
    lcd.print("Fan ON,");
  }
  else{
    lcd.print("Fan OFF,");
  }
  if(checkPump==1){
    lcd.print("Pump On");
  }
  else{
    lcd.print("Pump OFF");
  }

  lcd.setCursor(0,1);
  if(checkSpray==1){
    lcd.print("Spray ON");
  }
  else{
    lcd.print("Spray OFF");
  }
  delay(2500);

  lcd.clear();
  lcd.setCursor(0,0);
  if(checkLight==1){
    lcd.print("Light ON");
  }
  else{
    lcd.print("Light OFF");
  }

  lcd.setCursor(0,1);
  if(checkNichrome==1){
    lcd.print("Heater ON");
  }
  else{
    lcd.print("Heater OFF");
  }
  delay(2500);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("C, ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, ");
  Serial.print("Light Intensity: ");
  Serial.print(lux);
  Serial.print("lx, ");
  if(checkPump==1){
    Serial.println("LOW Moisture ");
  }
  else{
    Serial.println("HIGH Moisture ");
  }
  
 
    
  
}


