#include <ESP8266WiFi.h>
#include <Wire.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>



#define BOTtoken "6510119034:AAFd6fqo47fxM0a6QSB-j5TZAbMxvUR8tyM"
#define CHAT_ID "1595737437"

//float temperature,humidity,lux,value,volt;

//long myChannelNumber = 2237985;
//const char myWriteAPIKey[] = "V3ZHHDPXGY1TG225";
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("Mishti Kumra", "begun123");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  //dht.begin();
  //ThingSpeak.begin(client);
  
  //pinMode(LUX,INPUT);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  bot.sendMessage(CHAT_ID, "System started", "");
  delay(1000);
}


void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()>0){
    //char data = Serial.read();
    //Serial.readBytesUntil('\n',buffer,100);
    //Serisubstral.println(buffer);
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
    //int t = data.indexOf("Temperature");
    //int t_end = data.indexOf("C");
    //int h = data.indexOf("Humidity");
    //int h_end = data.indexOf("%");
    //int l = data.indexOf("Light");
    //int l_end = data.indexOf("lx");

    //if((t!=-1)&&(h!=-1)){
      //temperature = data.substring(t+12,t_end).toFloat();
     // humidity = data.substring(h+10,h_end).toFloat();
      //lux = data.substring(l+17,l_end).toFloat();
   // }
    bot.sendMessage(CHAT_ID, data , "");
  }
  //Serial.println("Temperature: " + (String) temperature + "C");
  //Serial.println("Humidity: " + (String) humidity + "%");
  //Serial.println("Light Intensity: " + (String)lux + "lx");
  //ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);
  //ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);
  //ThingSpeak.writeField(myChannelNumber, 3, lux, myWriteAPIKey);

  delay(5000);
}
