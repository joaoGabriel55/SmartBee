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
#define PUBLISH_INTERVAL 2000

//#define WIFI_SSID "Quaresma"
//#define WIFI_PASSWORD "15081967"

#define WIFI_SSID "Apontadoparauceu"
#define WIFI_PASSWORD "bufobufo"

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

void setup() {
  // put your setup code here, to run once:
  connectWifi();
  setupTime();
  pinSetup();
  // Registra o ticker para publicar de tempos em tempos
  ticker.attach_ms(PUBLISH_INTERVAL, publish);
}

void loop() {
  generateTime();

  if (publishNewState) {
    Serial.println("Publish new State");

    temperatura = tempRead();
    Serial.print("Temperatura = ");
    Serial.print(temperatura);
    Serial.println(" *C");
    if (!isnan(temperatura)) {
      // Manda para o firebase
      Firebase.pushFloat("temperature", temperatura);

      String buf = generateTime();
      buf.concat(";");
      buf.concat(temperatura);

      Firebase.pushString("temperatureDate", buf);
      Serial.println(generateTime());
      Serial.println(buf);

      publishNewState = false;
    } else {
      Serial.println("Error Publishing");
    }
  }
}
