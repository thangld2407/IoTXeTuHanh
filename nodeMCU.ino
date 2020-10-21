#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

//Define Firebase
#define FIREBASE_HOST "xetuhanhv3.firebaseio.com"
#define FIREBASE_AUTH "paLy29gNahA6MHh0vUzujFQ3ZrXf0W9Ne56e2f9U"
#define WIFI_SSID "IoT"
#define WIFI_PASSWORD "iotiot2020"


String myString;;

void sendDataMQ(){
  
  if(Serial.available()){
      Serial.print("ESP said: ");
  Serial.println(Serial.read());
  myString = Serial.read();
  Firebase.setString("Distance: ", myString);
    }  

}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  //pinMode MQ
  while(!Serial)
  {
     Serial.print(".");
     delay(500);
  }
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:

    sendDataMQ();
    delay(200);
}
