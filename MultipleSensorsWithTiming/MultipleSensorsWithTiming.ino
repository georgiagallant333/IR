
/*What program does
   1) measures micro seconds for each ball pulse
   2) takes NUMSAMPLES of these time readings
   3) stores them in an array
   4) returns average of 10 around median of the samples for each sensor
   5) starts another timer for each time the samples begin to be taken call noBallTimer
   6) if the noBallTimer gets over 20,000 microseconds, then it has taken too long to take the samples, and there is no ball

*/

#define NUMSAMPLES 20 //will disregard the last two samples (this is the number of pulses it takes before you can print/calculate average/etc.)
#define NUMSENSORS 7

int incrementSamples[NUMSENSORS]; //this increments separately for each sensor every pulse you count
long startTime[NUMSENSORS]; //this reads the time when the start of the pulse is read
byte currentReading[NUMSENSORS]; //reads the raw data for each sensor
byte pastReading[NUMSENSORS] = {1, 1, 1, 1, 1, 1, 1}; //stores the last reading for each sensor
boolean keepReading = 1; //keepReading goes to 0 if 20 samples have been taken
long noBallStartTime; //this reads the time when the first samples is taken
long sensorTimesHigh[NUMSENSORS][NUMSAMPLES]; //stores pulse duration for each sensor, and which sample that pulse was taken
int averages[NUMSENSORS]; //keeps track of the average time for pulse of 10 around median for each sensor
int closestSensor;
int angles[] = {0, 30, 60, 90, 120, 150, 180};

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); //lights up led to show program is running
  for (int x = 2; x < NUMSENSORS + 2; x++) {   //initializing pins starting on pin 2
    pinMode(x, INPUT);
  }
  noBallStartTime = micros(); //start ball timer
}

void loop() {
  readSensors(); //reads sensors and takes samples and sees if there is a ball or not
  printSensors();
  resetVariables();
}

void readSensors() {
  while (keepReading == 1) { //if keepReading is 1 then continue getting more samples
    for (int x = 2; x < NUMSENSORS + 2; x++) { //read all the sensors simultaneously and store in currentReading array
      currentReading[x - 2] = digitalReadFast(x);
    }
    for (int x = 0; x < NUMSENSORS; x++) { //cycles through sensors
      if (pastReading[x] == 1 && currentReading[x] == 0) { //if ball's pulse just went high, then start timer
        startTime[x] = micros();
      }
      else if (pastReading[x] == 0 && currentReading[x] == 1) { //if ball's pulse just went low, stop timer
        sensorTimesHigh[x][incrementSamples[x]] = micros() - startTime[x]; //store amount of time for pulse in array
        incrementSamples[x]++; //increment the sample you are on by 1
      }
      if (incrementSamples[x] == NUMSAMPLES) { //the first sensor to have the correct number of samples
        keepReading = 0; //don't keep reading a break out of keepReading loop
        break;
      }
      pastReading[x] = currentReading[x]; //every time it cycles the pastReading is set to the current Reading
    }
    //   if (micros() - noBallStartTime > 20000) { //if the current time - the time it was from when the first sample of this cycle was taken is long than there isn't a ball
    //Serial.println("NO BALL");
    //   }
    //  else { //otherwise there is a ball
    //     //Serial.println("BALL");
  }
}
//if 20 samples have been taken
//  sortArrayAndGetAverage(); //sorts each sensors samples in increasing order get average of the 10 around the median

//  findAngle();

//}

/*void sortArrayAndGetAverage() {
  for (int i = 0; i < NUMSENSORS; i++) {
    insertion_sort(sensorTimesHigh[i], NUMSAMPLES); //sorts the times for each sensor in increasing order
    averages[i] = getAverage(sensorTimesHigh[i]);
    //Serial.print(averages[i]);
    //Serial.print("  ");
    if (averages[i] < averages[closestSensor]) {
      closestSensor = i;
    }
  }
  //Serial.println(" ");
  }

  void findAngle() {
  int difference = averages[closestSensor + 1] - averages[closestSensor - 1];
  int ballAngle;
  Serial.println(closestSensor);
  //  Serial.print(", ");
  //  Serial.print(difference);
  //  Serial.print(", ");
  if (difference > 0) {
    ballAngle = angles[closestSensor] + (difference / 5.3);
  }
  else {
    ballAngle = angles[closestSensor] - (difference / 5.3);
  }
  //Serial.println(ballAngle);
  }
  void insertion_sort (long arr[], int length) { //insertion sort goes through array once, fast sort
  int j;
  long temp;
  for (int j = 1; j < length; j++) {
    while (j > 0 && arr[j] < arr[j - 1]) {
      temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
      j--;
    }
  }
  }*/

long getAverage(long arr[]) {
  long sum = 0;
  long avg = 0;
  for (int i = ((NUMSAMPLES / 2) - 5) ; i < ((NUMSAMPLES / 2) + 5); i++) { // for( int i =  median - 5; i < median + 5; i++)
    sum = sum + arr[i];
  }
  avg = sum / 10;
  return avg;
}

void resetVariables() {
  noBallStartTime = micros(); //retake time for calculating if it has been too long for the samples to be taken
  keepReading = 1; //can keep reading sensors
  for (int i = 0; i < NUMSENSORS; i++) { //resetting array to store time to 0
    incrementSamples[i] = 0;
    pastReading[i] = 1;
    for (int x = 0; x < NUMSAMPLES; x++) { //resetting sensorTimesHigh to 0
      sensorTimesHigh[i][x] = 0;
    }
  }
}

void printSensors() {
  Serial.println("\nNEW SERIES");
  for (int b = 0; b < NUMSENSORS; b++) {
    Serial.print(b);
    Serial.print(": ");
    for (int a = 0; a < NUMSAMPLES; a++) {
      Serial.print(sensorTimesHigh[b][a]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }

}


