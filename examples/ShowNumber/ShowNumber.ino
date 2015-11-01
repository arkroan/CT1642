#include <CT1642.h>

// Define the CT1642 pins
#define CLOCK_PIN 6
#define DATA_PIN  7

// Setup an instance to communicate the CT1642 IC
CT1642 ledDriver(CLOCK_PIN, DATA_PIN);

void setup() {

}

void loop() {


  int value = 9999;

  // Show a number
  ledDriver.showNumber(value);

  // for numbers > 9999 and numbers < 0 
  // the result is either 9999 or 0
//  ledDriver.showNumber(value+10);
//  ledDriver.showNumber(10-value);

}
