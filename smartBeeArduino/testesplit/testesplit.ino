void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  String part01 = getValue("23.9523.0030.0023.95;23.00;30.00", ';', 0);
  String part02 = getValue("23.9523.0030.0023.95;23.00;30.00", ';', 1);
  String part03 = getValue("23.9523.0030.0023.95;23.00;30.00", ';', 2);

  Serial.println(part01);
  Serial.println(part02);
  Serial.println(part03);
  delay(1000);

}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
