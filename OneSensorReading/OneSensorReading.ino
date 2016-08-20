void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
    uint8_t currentReading = PIND;
    Serial.println(bitRead(currentReading,3), BIN);


}


