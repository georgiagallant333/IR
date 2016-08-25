#define NUMSAMPLES 20 
#define NUMSENSORS 7

int incrementSamples[7];
long startTime[7];
byte currentReading[7];
byte pastReading[7];
boolean endLoop = 0;

long sensorTimesHigh[NUMSENSORS][NUMSAMPLES];


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  //initializing pins
  for (int x = 2; x < NUMSENSORS + 2; x++) {
    pinMode(x, INPUT);
  }
}

void loop() {
  readSensors();
  if (endLoop == 1) {
    resetVariables();
    printSensors();
  }
}
void printSensors() {
  Serial.println("\nNEW SERIES");
  for (int a = 1; a < NUMSAMPLES - 1; a++) {
    for (int b = 0; b < NUMSENSORS; b++) {
      Serial.print(b);
      Serial.print(": ");
      Serial.print(sensorTimesHigh[b][a]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
}


void resetVariables() {
  endLoop = 0;
  for (int i = 0; i < NUMSENSORS; i++) {
    incrementSamples[i] = 0;
  }
  for (int i = 0; i < NUMSENSORS; i++) {
    startTime[i] = 0;
    pastReading[i] = 0;
  }
}

void readSensors() {
  if (endLoop == 0) {
    for (int x = 2; x < NUMSENSORS + 2; x++) {
      currentReading[x - 2] = digitalReadFast(x);
    }
    for (int x = 0; x < NUMSENSORS; x++) {
      if (pastReading[x] == 1 && currentReading[x] == 0) {
        startTime[x] = micros();
      }
      else if (pastReading[x] == 0 && currentReading[x] == 1) {
        sensorTimesHigh[x][incrementSamples[x]] = micros() - startTime[x];
        incrementSamples[x]++;
      }
      if (incrementSamples[x] == NUMSAMPLES) {
        endLoop = 1;
      }
      pastReading[x] = currentReading[x];
    }
  }
}

