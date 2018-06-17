#include <DHT.h>
//#include <SoftwareSerial.h>

#define DHTPIN A2     // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int sensor = 0;
const int LM35 = A1;
float tempColmeia1 = 0;

//SoftwareSerial ArduinoUno(3,2);

String valoresToSend;
String valorSend;

void setup() {
  // put your setup code here, to run once: 
  //Serial.println("DHTxx test!");
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  //Serial.print("Temperatura = ");
  //Serial.print(tempColmeia1);
  //Serial.println(" *C");

  // put your main code here, to run repeatedly:
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  
  tempColmeia1 = tempReadColmeia();
  
  float humidade = dht.readHumidity();
  float tempColmeia2 = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(tempColmeia2) || isnan(humidade)) {
    Serial.println("Failed to read from DHT");
  }
  
  else {
    //Serial.print("Umidade: ");
    //Serial.print(" %t");
    //Serial.print("Temperatura: ");
    //Serial.print(tempColmeia2);
    //Serial.print(humidade);
    //Serial.println(" *C");
    sendSerialNode(tempColmeia1, tempColmeia2, humidade);
    delay(1000);
  }
}

float tempReadColmeia() {

  sensor = analogRead(LM35);
  //float millivolts = ( sensor / 1024.0) * 3000;
  tempColmeia1 = (float(analogRead(LM35)) * 5 / (1023)) / 0.01;
  delay(500);

  return tempColmeia1;
}

void sendSerialNode(float tempColmeia1, float tempColmeia2, float humidade) {
  String temp1;
  String temp2;
  String humid;

  //Var para auxiliar na conversão de "String" para "char"
  char copy[50];
  
  String valoresConcat;

  if (!isnan(tempColmeia1) && !isnan(tempColmeia2) && !isnan(humidade)) {
    temp1 = String(tempColmeia1);
    temp2 = String(tempColmeia2);
    humid = String(humidade);
    
    valoresConcat = temp1 + ";" + temp2 + ";" + humid + ":";
    Serial.println(valoresConcat);
    //Serial.write("TESTA:");
    //delay(5000);
  } else {
    Serial.print("ERROR");
  }

}
