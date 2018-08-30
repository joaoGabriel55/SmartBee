#include <DHT.h>
//#include <SoftwareSerial.h>
#include "HX711.h" // Biblioteca HX711

#define DHTPIN A2     // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

//-------------------- Peso -------------------------//
#define DOUT A0 // HX711 DATA OUT = pino A0 do Arduino
#define CLK A1 // HX711 SCK IN = pino A1 do Arduino

HX711 balanca(DOUT, CLK); // instancia Balança HX711
float calibration_factor = 21700; // fator de calibração aferido na Calibraçao
//--------------------------------------------------//

DHT dht(DHTPIN, DHTTYPE);
//DT SCK
int sensor = 0;
//const int LM35 = A1;
//SoftwareSerial ArduinoUno(3,2);

String valoresToSend;
String valorSend;

void setup() {
  // put your setup code here, to run once:
  //Serial.println("DHTxx test!");
  Serial.begin(115200);
  dht.begin();

  balanca.set_scale(calibration_factor); // ajusta fator de calibração
  balanca.tare(); // zera a Balança
}

void loop() {
  //Serial.print("Temperatura = ");
  //Serial.print(tempColmeia1);
  //Serial.println(" *C");

  float peso = balanca.get_units();

  float humidade = dht.readHumidity();
  float tempColmeia1 = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(tempColmeia1) || isnan(humidade)) {
    Serial.println("Failed to read from DHT");
  }

  else {
    //Serial.print("Umidade: ");
    //Serial.print(" %t");
    //Serial.print("Temperatura: ");
    //Serial.print(tempColmeia2);
    //Serial.print(humidade);
    //Serial.println(" *C");
    sendSerialNode(tempColmeia1, peso, humidade);
    delay(1000);
  }
}

//float tempReadColmeia() {
//
//  sensor = analogRead(LM35);
//  //float millivolts = ( sensor / 1024.0) * 3000;
//  tempColmeia1 = (float(analogRead(LM35)) * 5 / (1023)) / 0.01;
//  delay(500);
//
//  return tempColmeia1;
//}

void sendSerialNode(float tempColmeia1, float pesoColmeia1, float humidade) {
  String temp1;
  String peso;
  String humid;

  //Var para auxiliar na conversão de "String" para "char"
  char copy[50];

  String valoresConcat;

//  if (Serial.available() > 0) {
//    char calibracao = (byte)Serial.read();
//    Serial.println(calibracao);
//  }

  if (!isnan(tempColmeia1) &&
      !isnan(humidade)) {

    temp1 = String(tempColmeia1);
    peso = String(pesoColmeia1);
    humid = String(humidade);

    valoresConcat = temp1 + ";" + peso + ";" + humid + ":";
    Serial.println(valoresConcat);
    //Serial.write("TESTA:");
    //delay(5000);
  } else {
    Serial.print("ERROR");
  }

}

