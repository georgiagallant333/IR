#define NUMSAMPLES 20
#define NUMSENSORS 7

int incrementSamples[7];
long startTime[7];
byte currentReading[7];
byte pastReading[7];
boolean endLoop = 0;
long noBallStartTime;
long sensorTimesHigh[NUMSENSORS][NUMSAMPLES];


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  //initializing pins
  for (int x = 2; x < NUMSENSORS + 2; x++) {
    pinMode(x, INPUT);
  }
  noBallStartTime = micros();
}

void loop() {
  readSensors();
  if (endLoop == 1) {
    sortArrayAndGetAverage();
    resetVariables();
    // printSensors();
  }
}
void printSensors() {
  Serial.println("\nNEW SERIES");
  for (int a = 0; a < NUMSAMPLES; a++) {
    Serial.print(a);
    Serial.print(": ");
    for (int b = 0; b < NUMSENSORS; b++) {
      Serial.print(b);
      Serial.print(": ");
      Serial.print(sensorTimesHigh[b][a]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
}

long getAverage(long arr[]) {
  long sum = 0;
  long avg = 0;
  for (int i = ((NUMSAMPLES / 2) - 5); i < ((NUMSAMPLES / 2) + 5); i++) {
    sum = sum + arr[i];
  }
  avg = (float)sum / 10;
  return avg;
}

void sortArrayAndGetAverage() {
  boolean noBall[7];
  for (int i = 0; i < NUMSENSORS; i++) {
    insertion_sort(sensorTimesHigh[i], NUMSAMPLES);
    getAverage(sensorTimesHigh[i]);
  }
}


void insertion_sort (long arr[], int length) {
  int j, temp;
  for (int j = 1; j < length; j++) {
    while (j > 0 && arr[j] < arr[j - 1]) {
      temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
      j--;
    }
  }
}


void resetVariables() {
  noBallStartTime = micros();
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
    if (micros() - noBallStartTime > 20000) {
      Serial.println("NO BALL");
    }
    else{
      Serial.println("BALL");
    }
  }
}

