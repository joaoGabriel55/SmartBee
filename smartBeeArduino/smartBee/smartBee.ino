#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <math.h>
#include <String.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "Arduino.h"

#pragma once
#include <time.h>
#include <Udp.h>

WiFiUDP ntpUDP;
/*Var for time*/
int16_t utc = -3; //UTC -3:00 Brazil
uint32_t currentMillis = 0;
uint32_t previousMillis = 0;

NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc * 3600, 60000);

#define FIREBASE_HOST "smartbee-3239b.firebaseio.com"
#define FIREBASE_AUTH "WOvd0SNDEHZ9o00lMOgHBOPTXcuMUTGXAyx41qYe"
#define PUBLISH_INTERVAL 10000

//#define WIFI_SSID "Quaresma"
//#define WIFI_PASSWORD "15081967"

//#define WIFI_SSID "Apontadoparauceu"
//#define WIFI_PASSWORD "bufobufo"
#define WIFI_SSID "UFRN - EAJ - UBICOMP"
#define WIFI_PASSWORD "cuscuzcomovo"

// valores que serao recebidos pelo Arduino UNO
String valoresToReceive;
String valorReceived;

int sensor = 0;
const int LM35 = 0;
float temperatura = 0;

Ticker ticker;
bool publishNewState = true;

void publish() {
  publishNewState = true;
}

void connectWifi() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// forçar a atualização do relógio no servidor NTP.
void forceUpdate(void) {
  timeClient.forceUpdate();
}

void setupTime() {
  timeClient.begin();
  timeClient.update();
}

String generateTime() {
  currentMillis = millis();//Tempo atual em ms
  //Lógica de verificação do tempo
  if (currentMillis - previousMillis > 1000) {
    previousMillis = currentMillis;    // Salva o tempo atual
    //printf("Time Epoch: %d: ", timeClient.getEpochTime());
    timeClient.getFormattedTime();
  }

  return timeClient.getFullFormattedTime();
}

void pinSetup() {
  //    pinMode(ledPin, OUTPUT);
  //    pinMode(ledPin2, OUTPUT);
  //    pinMode(ledPin3, OUTPUT);
  //    pinMode(ventoinha, OUTPUT);
  //    pinMode(presenca2, OUTPUT);
  //    pinMode(buzzer, OUTPUT);
  //    pinMode(presenca, INPUT);
  //
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //    Firebase.setBool("led", false);
  //    Firebase.setBool("led2", false);
  //    Firebase.setBool("led3", false);
  //    Firebase.setBool("presence", false);
  //    Firebase.setBool("presence_switch", false);
  //    Firebase.setBool("arCondicionado", false);

}

float tempRead() {

  sensor = analogRead(LM35);
  float millivolts = ( sensor / 1024.0) * 3000;
  temperatura = millivolts / 10;
  delay(500);

  return temperatura;

}

String getDataBySerial(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void receiveDataMega(){
    while(Serial.available() > 0){
          valorReceived = (byte)Serial.read();
          if(valorReceived == ":"){
            
            String temp1 = getDataBySerial(valoresToReceive, ';', 0);
            String temp2 = getDataBySerial(valoresToReceive, ';', 1);
            String humidade = getDataBySerial(valoresToReceive, ';', 2);

            Serial.println(temp1);
            Serial.println(temp2);
            Serial.println(humidade);
            
//            int v = atoi(valor.c_str());
//            if(led=="/leds/led15"){
//               Firebase.setInt(led, v);
//            }
            
            valoresToReceive="";
            break;  
          }else{
             valoresToReceive += valorReceived;
          }
          delay(1);
    }
 }

void setup() {
  // put your setup code here, to run once:
  Serial.write("CONNECTED:");
  connectWifi();
  setupTime();
  pinSetup();
  // Registra o ticker para publicar de tempos em tempos
  ticker.attach_ms(PUBLISH_INTERVAL, publish);
}

void loop() {
  generateTime();

  if (publishNewState) {
    //Serial.println("Publish new State");

    temperatura = tempRead();
    //Serial.print("Temperatura = ");
    //Serial.print(temperatura);
    //Serial.println(" *C");
    if (!isnan(temperatura)) {
      // Manda para o firebase
      Firebase.pushFloat("temperature", temperatura);

      String buf = generateTime();
      buf.concat(";");
      buf.concat(temperatura);

      Firebase.pushString("temperatureDate", buf);
      //Serial.println(generateTime());
      //Serial.println(buf);

      receiveDataMega();

      publishNewState = false;
    } else {
      Serial.println("Error Publishing");
    }
  }
}
