#include <DHT.h>

#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int sensor = 0;
const int LM35 = A2;
float tempColmeia1 = 0;

String valoresToSend;
String valorSend;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  //Serial.println("DHTxx test!");
  dht.begin();
}

void loop() {

  tempColmeia1 = tempReadColmeia2();
  //Serial.print("Temperatura = ");
  Serial.print(tempColmeia1);
  //Serial.println(" *C");

  // put your main code here, to run repeatedly:
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float humidade = dht.readHumidity();
  float tempColmeia2 = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(tempColmeia2) || isnan(humidade))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    //Serial.print("Umidade: ");
    
    //Serial.print(" %t");
    //Serial.print("Temperatura: ");
    Serial.print(tempColmeia2);
    Serial.print(humidade);
    //Serial.println(" *C");
    sendSerialNode(tempColmeia1, tempColmeia2, humidade);
    lerStatusConexao();
    delay(10000);
  }

  
}

float tempReadColmeia2() {

  sensor = analogRead(LM35);
  //float millivolts = ( sensor / 1024.0) * 3000;
  tempColmeia1 = (float(analogRead(LM35))*5/(1023))/0.01;
  delay(500);

  return tempColmeia1;

}

void sendSerialNode(float tempColmeia1, float tempColmeia2, float humidade) {
  String temp1;
  String temp2;
  String humid;
  String valoresConcat;
  
  if (!isnan(tempColmeia1) && !isnan(tempColmeia2) && !isnan(humidade)) {
    temp1 = String(tempColmeia1);
    temp2 = String(tempColmeia2);
    humid = String(humidade);
  } else {
    Serial.print("ERROR");
  }
  valoresConcat = temp1 + ";" + temp2 + ";" + humid + ":";
  Serial.print(valoresConcat);
}

void lerStatusConexao() {
  bool flag = false;
  while (Serial.available() > 0) {

    valorSend = (byte)Serial.read();
    if (valorSend == ':') {
      if (valoresToSend == "CONNECTED") {
            Serial.print("OK!!!");
      }
      valoresToSend = "";
      break;
    } else {
      if (flag)
        valoresToSend += valorSend;
    }
    delay(1);
  }
}


