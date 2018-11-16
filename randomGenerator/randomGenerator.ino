int millisZero;

void setup() {
  Serial.begin(25000);
  millisZero=millis();
}

void loop() {
  float maValeur=75+25*sin((millisZero-millis())/1000)+random(-4,4);
  Serial.println(maValeur);
  delay(75);
}
