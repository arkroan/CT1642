#include <CT1642.h>

// Define the CT1642 pins
#define CLOCK_PIN 6
#define DATA_PIN  7

// Setup an instance to communicate the CT1642 IC
CT1642 ledDriver(CLOCK_PIN, DATA_PIN);

void setup() {

}

void loop() {

  int hours = 15;
  int minutes = 59;
  
  // Display Time
  ledDriver.showTime(hours, minutes);

}
