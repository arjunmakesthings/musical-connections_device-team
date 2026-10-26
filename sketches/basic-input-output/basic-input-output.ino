/*
basic sketch to show input-output possibilities.

arjun; 261026. 
*/

//include libraries:
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lidar = Adafruit_VL53L0X();

//for the lidar:
int distance = 0;
int frequency = 0;
int duration = 0;

const int speaker = 9; 
const int pot = A7; 

void setup() {
  if (!lidar.begin()) {
    while (1); // <-- to not move ahead until lidar is good to go.
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lidar.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) { //to not have failures; from the examples:
    distance = measure.RangeMilliMeter; //change range to mm.

    //mapping:
    distance = constrain(distance, 50, 400);
    frequency = map(distance, 50, 400, 200, 1000);

    //change duration with the pot:
    duration = map(analogRead(potpin), 0, 1023, 20, 500);

    //play the note:
    tone(speakerpin, frequency, duration);
    delay(duration);
  }
}
