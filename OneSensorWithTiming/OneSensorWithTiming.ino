#define NUMSAMPLES 10

int incrementSamples = 0;
long startTime = 0;
long finalTime = 0;
int pastReading = 0;
long sensorTimesHigh[NUMSAMPLES];

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);

}

void loop() {
  if(incrementSamples < NUMSAMPLES){
    //byte currentReading = bitRead(PIND, 2);
    byte currentReading = GPIOD_PDIR & 0xFF;
    if (pastReading == 1 && currentReading == 0) {
      startTime = micros();
    }
    else if (pastReading == 0 && currentReading == 1) {
      finalTime = micros() - startTime;
      sensorTimesHigh[incrementSamples] = finalTime;
      incrementSamples++;
      digitalWrite(13, HIGH);
    }
    pastReading = currentReading;
  }

 if(incrementSamples == NUMSAMPLES){
    digitalWrite(13, LOW);
    incrementSamples = 0;
    Serial.println(" ");
    for (int a = 0; a < NUMSAMPLES; a++) {
      Serial.println(sensorTimesHigh[a]);
    }
  }

}


