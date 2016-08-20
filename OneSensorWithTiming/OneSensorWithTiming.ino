#define NUMSAMPLES 100

int incrementSamples = 0;
long startTime = 0;
long finalTime = 0;
int pastReading = 0;
long sensorTimesHigh[NUMSAMPLES];

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  delay(5000);
  while (incrementSamples < NUMSAMPLES) {
    digitalWrite(13, HIGH);
    uint8_t currentReading = PIND;
    uint8_t pin2 = bitRead(currentReading, 0);
    Serial.println(pin2);
    if (pastReading == 0 && currentReading == 1) {
      startTime = micros();
    }
    else if (pastReading == 1 && currentReading == 0) {
      finalTime = micros() - startTime;
      sensorTimesHigh[incrementSamples] = finalTime;
      incrementSamples++;

    }
    pastReading = currentReading;
  }
    digitalWrite(13, LOW);
    incrementSamples = 0;
    Serial.println(" ");
    for (int a = 0; a < NUMSAMPLES; a++) {
      Serial.println(sensorTimesHigh[a]);
  }
}

void loop() {


}


