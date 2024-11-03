// Define pin numbers
const int trigPin = 9;
const int echoPin = 10;
const int touchPin = 11;

// Define 7-segment display pins
const int segmentA = 2;
const int segmentB = 3;
const int segmentC = 4;
const int segmentD = 5;
const int segmentE = 6;
const int segmentF = 7;
const int segmentG = 8;

// Countdown duration in seconds
const int countdownDuration = 10; // Set the countdown time here
const int distanceThreshold = 20; // Distance threshold in cm

void setup() {
    Serial.begin(9600);

    // Set up pins for the ultrasonic sensor
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    // Set up pins for the touch sensor
    pinMode(touchPin, INPUT);
    
    // Set up pins for the 7-segment display
    pinMode(segmentA, OUTPUT);
    pinMode(segmentB, OUTPUT);
    pinMode(segmentC, OUTPUT);
    pinMode(segmentD, OUTPUT);
    pinMode(segmentE, OUTPUT);
    pinMode(segmentF, OUTPUT);
    pinMode(segmentG, OUTPUT);
}

void loop() {
    // Check if the touch sensor is activated
    if (digitalRead(touchPin) == HIGH) {
        startCountdown();
    }

    delay(100); // Debounce delay
}

void startCountdown() {
    for (int i = countdownDuration; i >= 0; i--) {
        displayNumber(i);
        
        // Check for obstacles during countdown
        if (getDistance() < distanceThreshold) {
            // Reset countdown if an obstacle is detected
            i = countdownDuration; // Reset to original countdown value
        }
        
        delay(1000); // Wait for 1 second
    }

    // Display "E" when countdown is complete
    displayComplete();
}

long getDistance() {
    // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Set the trigPin HIGH for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echoPin
    long duration = pulseIn(echoPin, HIGH);
    
    // Calculate distance (in cm)
    return duration * 0.034 / 2;
}

void displayNumber(int num) {
    clearDisplay(); // Clear display before showing new number

    // Handle numbers from 0 to 9
    switch(num) {
        case 0:
            digitalWrite(segmentA, HIGH);
            digitalWrite(segmentB, HIGH);
            digitalWrite(segmentC, HIGH);
            digitalWrite(segmentD, HIGH);
            digitalWrite(segmentE, HIGH);
            digitalWrite(segmentF, HIGH);
            break;
        case 1:
            digitalWrite(segmentB, HIGH);
            digitalWrite(segmentC, HIGH);
            break;
        case 2:
            digitalWrite(segmentA, HIGH);
            digitalWrite(segmentB, HIGH);
            digitalWrite(segmentD, HIGH);
            digitalWrite(segmentE, HIGH);
            digitalWrite(segmentG, HIGH);
            break;
        case 3:
            digitalWrite(segmentA, HIGH);
            digitalWrite(segmentB, HIGH);
            digitalWrite(segmentC, HIGH);
            digitalWrite(segmentD, HIGH);
            digitalWrite(segmentG, HIGH);
            break;
        case 4:
            digitalWrite(segmentB, HIGH);
            digitalWrite(segmentC, HIGH);
            digitalWrite(segmentF, HIGH);
            digitalWrite(segmentG, HIGH);
            break;
        case 5:
            digitalWrite(segmentA, HIGH);
            digitalWrite(segmentC, HIGH);
            digitalWrite(segmentD, HIGH);
            digitalWrite(segmentF, HIGH);
            digitalWrite(segmentG, HIGH);
            break;
        case 6:
            digitalWrite(segmentA, HIGH);
            digitalWrite(segmentC, HIGH);
            digitalWrite(segmentD, HIGH);
            digitalWrite(segmentE, HIGH);
            digitalWrite(segmentF, HIGH);
            digitalWrite(segmentG, HIGH);
            break;
        case 7:
            digitalWrite(segmentA, HIGH);
            digitalWrite(segmentB, HIGH);
            digitalWrite(segmentC, HIGH);
            break;
        case 8:
            digitalWrite(segmentA, HIGH);
            digitalWrite(segmentB, HIGH);
            digitalWrite(segmentC, HIGH);
            digitalWrite(segmentD, HIGH);
            digitalWrite(segmentE, HIGH);
            digitalWrite(segmentF, HIGH);
            digitalWrite(segmentG, HIGH);
            break;
        case 9:
            digitalWrite(segmentA, HIGH);
            digitalWrite(segmentB, HIGH);
            digitalWrite(segmentC, HIGH);
            digitalWrite(segmentD, HIGH);
            digitalWrite(segmentF, HIGH);
            digitalWrite(segmentG, HIGH);
            break;
    }
}

void clearDisplay() {
    // Turn off all segments
    digitalWrite(segmentA, LOW);
    digitalWrite(segmentB, LOW);
    digitalWrite(segmentC, LOW);
    digitalWrite(segmentD, LOW);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, LOW);
    digitalWrite(segmentG, LOW);
}

void displayComplete() {
    clearDisplay();
    // Display "E" (Assuming segments for "E" are a, f, g, d, e)
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
}
