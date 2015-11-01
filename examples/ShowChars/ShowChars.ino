#include <CT1642.h>

// Define the CT1642 pins
#define CLOCK_PIN 6
#define DATA_PIN  7

// Setup an instance to communicate the CT1642 IC
CT1642 ledDriver(CLOCK_PIN, DATA_PIN);

void setup() {

  // Set the delay in ms between each digit for POV (optional). Default is 2ms
  ledDriver.setPovDelay(4);

}

void loop() {

  // Show Characters
  ledDriver.showChars('E', 'r' , 'r', '1');

}
