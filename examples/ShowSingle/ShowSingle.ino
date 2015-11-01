#include <CT1642.h>

// Define the CT1642 pins
#define CLOCK_PIN 6
#define DATA_PIN  7

// Setup an instance to communicate the CT1642 IC
CT1642 ledDriver(CLOCK_PIN, DATA_PIN);

void setup() {
  // Set Persistence of Vision Delay
  // In other words, set the time 
  // each segment is active
  ledDriver.setPovDelay(1000);
}

void loop() {

  // Display a single number on a single digit
  // (int number, int digit)
  ledDriver.showSingle(1,1);
  delay(2000);
  ledDriver.showSingle(2,2);
  delay(2000);
  ledDriver.showSingle(3,3);
  delay(2000);
  ledDriver.showSingle(4,4);
  delay(2000);

}
