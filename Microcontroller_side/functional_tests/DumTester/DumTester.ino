

void setup() {
  Serial.begin(115200);
  // Serial.println("ready");
}

void loop() {

  int value = analogRead(5);

/*
  Serial.print(value);
  Serial.print("\t");
  Serial.print(value / 1024.);
  Serial.println("");
*/
  Serial.write(0b00000001);
  delay(1000);
  Serial.write(0b00000010);
  delay(1000);
  Serial.write(0b00000100);
  delay(1000);
  Serial.write(0b00001000);
  delay(1000);
}
