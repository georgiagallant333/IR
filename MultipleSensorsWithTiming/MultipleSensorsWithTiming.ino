#define NUMSAMPLES 20
#define NUMSENSORS 7

int incrementSamples[NUMSAMPLES];
long startTime[7];
long finalTime[7];
byte currentReading[7];
byte pastReading[7];

long sensorTimesHigh[NUMSENSORS][NUMSAMPLES];

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  for (int x = 2; x < 9; x++) {
    pinMode(x, INPUT);
  }

}

void loop() {
  for (int x = 2; x < 9; x++) {
    currentReading[x - 2] = digitalReadFast(x);
  }
  for (int x = 0; x < 7; x++) {
    if (pastReading[x] == 1 && currentReading[x] == 0) {
      startTime[x] = micros();
    }
    else if (pastReading[x] == 0 && currentReading[x] == 1) {
      finalTime[x] = micros() - startTime[x];
      sensorTimesHigh[x][incrementSamples[x]] = finalTime[x];
      incrementSamples[x]++;
    }
    pastReading[x] = currentReading[x];
    if (incrementSamples[x] == NUMSAMPLES) {
      incrementSamples[x] = 0;
      for (int a = 0; a < NUMSAMPLES; a++) {
        for (int b = 0; b < 7; b++) {
          Serial.print(b);
          Serial.print(": ");
          Serial.println(sensorTimesHigh[b][a]);
        }
      }
    }
  }
}



