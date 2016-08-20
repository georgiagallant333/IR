void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2,INPUT); 
}

void loop() {
    byte currentReading = GPIOD_PDIR & 0xFF;
    Serial.println(currentReading, HEX);
}


