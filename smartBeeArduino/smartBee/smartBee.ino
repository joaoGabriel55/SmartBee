#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <math.h>

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

void setup() {
  // put your setup code here, to run once:
  connectWifi();
  pinSetup();
  // Registra o ticker para publicar de tempos em tempos
  ticker.attach_ms(PUBLISH_INTERVAL, publish);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (publishNewState) {
    Serial.println("Publish new State");

    temperatura = tempRead();
    Serial.print("Temperatura = ");
    Serial.print(temperatura);
    Serial.println(" *C");
    if (!isnan(temperatura)) {
      // Manda para o firebase
      Firebase.pushFloat("temperature", temperatura);
      publishNewState = false;
    } else {
      Serial.println("Error Publishing");
    }
  }

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

