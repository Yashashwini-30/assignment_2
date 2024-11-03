#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with the I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 if necessary

// Define button pins
const int buttonStartStopPin = 2;
const int buttonResetPin = 3;

// Stopwatch variables
volatile bool running = false;
volatile unsigned long elapsedTime = 0;
unsigned long previousMillis = 0;

void setup() {
    lcd.begin();
    lcd.backlight();

    pinMode(buttonStartStopPin, INPUT);
    pinMode(buttonResetPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(buttonStartStopPin), toggleStopwatch, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonResetPin), resetStopwatch, FALLING);
}

void loop() {
    if (running) {
        unsigned long currentMillis = millis();
        elapsedTime += currentMillis - previousMillis;
        previousMillis = currentMillis;
    }

    // Display the elapsed time in seconds and milliseconds
    displayTime(elapsedTime);

    delay(100); // Update display every 100ms
}

void toggleStopwatch() {
    running = !running;
    if (running) {
        previousMillis = millis(); // Reset the timer
    }
}

void resetStopwatch() {
    running = false;
    elapsedTime = 0; // Reset elapsed time
    displayTime(elapsedTime); // Clear the display
}

void displayTime(unsigned long time) {
    unsigned long seconds = time / 1000; // Convert to seconds
    unsigned long milliseconds = time % 1000; // Get the remaining milliseconds
    unsigned long displaySeconds = seconds % 60; // Get seconds for display
    unsigned long displayMinutes = (seconds / 60) % 60; // Get minutes for display
    unsigned long displayHours = seconds / 3600; // Get hours for display

    // Clear the display
    lcd.clear();

    // Format and print the time
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.print(displayHours);
    lcd.print(":");
    if (displayMinutes < 10) lcd.print("0");
    lcd.print(displayMinutes);
    lcd.print(":");
    if (displaySeconds < 10) lcd.print("0");
    lcd.print(displaySeconds);
    lcd.print(".");
    lcd.print(milliseconds / 10); // Print tenths of seconds
}
