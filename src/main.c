#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>

// Define the pin numbers
const int ledPin = 14;    // GPIO 14
const int buttonPin = 4;  // GPIO 4

// Toggle the LED state when the button is pressed
void toggleLED() {
    static bool ledState = false;
    ledState = !ledState;  // Toggle the LED state
    digitalWrite(ledPin, ledState ? HIGH : LOW);
}

int main() {
    // Initialize the wiringPi library
    if (wiringPiSetupGpio() == -1) {
        printf("Failed to initialize wiringPi\n");
        return -1;
    }

    // Set the pin modes
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);

    // Enable the pull-up resistor for the button pin
    pullUpDnControl(buttonPin, PUD_UP);

    // Loop to detect button presses and toggle the LED
    while (1) {
        // Print the button state
        printf("Button state: %d\n", digitalRead(buttonPin));

        // Check if the button is pressed
        if (digitalRead(buttonPin) == HIGH) {
            toggleLED();
            delay(300);  // Debouncing delay
        }

        delay(50);  // Short delay to reduce CPU usage
    }

    return 0;
}
