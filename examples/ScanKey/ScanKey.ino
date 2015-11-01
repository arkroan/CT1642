#include <CT1642.h>

// Pins according to the schematic
#define CLOCK_PIN 6
#define DATA_PIN  7
#define KEY_PIN   3   // Make sure this is an Interrupt PIN

// Setup an instance to communicate the CT1642 IC (including key scan function).
CT1642 ledDriver(CLOCK_PIN, DATA_PIN, KEY_PIN);

// Variables for the Interrupt
// and Button Debouncing
boolean btnPressed ;
volatile int key_pressed;
volatile unsigned long last_micros;
long debouncing_time = 200; // in Milliseconds

void setup(void) {

  // start serial port
  Serial.begin(115200);

  // IC CT1642 Key Interrupt. Recomended Rising Edge.
  attachInterrupt(digitalPinToInterrupt(KEY_PIN), btnPress, RISING);

  // Set Persistence of Vision Delay for the Display
  ledDriver.setPovDelay(15);

  btnPressed = false;
  key_pressed = 0;
}

void loop(void) {

  // Display the number of the button pressed on the last digit
  ledDriver.showSingle(key_pressed,4);

  // button pressed
  if (btnPressed) {
    // Write result to serial
    Serial.print("Button press read: ");
    Serial.print(key_pressed);
    Serial.print(", B-");
    Serial.print(key_pressed, BIN);
    Serial.print(", Hex-");
    Serial.println(key_pressed, HEX);

    // Debounce Serial
    btnPressed = false;
  }
}

// Function for the interrupt
void btnPress() {

  // Disable interrupts for now
  noInterrupts();
  // Debounce button
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {
    if (!btnPressed) {
      btnPressed = true;
      // Get the key code from the CT1642
      key_pressed = ledDriver.getKeyCode();
    }
    last_micros = micros();
  }
  // Enable interrupts
  interrupts();
}

