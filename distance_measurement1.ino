// Define pin numbers
const int trigPin = 9;
const int echoPin = 10;

// Define 7-segment display pins
const int segmentA = 2;
const int segmentB = 3;
const int segmentC = 4;
const int segmentD = 5;
const int segmentE = 6;
const int segmentF = 7;
const int segmentG = 8;

void setup() {
    Serial.begin(9600);

    // Set up pins for the ultrasonic sensor
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
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
    long duration, distance;

    // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Set the trigPin HIGH for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echoPin
    duration = pulseIn(echoPin, HIGH);

    // Calculate distance (in cm)
    distance = duration * 0.034 / 2;

    // Display distance on the 7-segment display
    displayNumber(distance);

    // Wait before the next measurement
    delay(500);
}

void displayNumber(int num) {
    // Turn off all segments
    digitalWrite(segmentA, LOW);
    digitalWrite(segmentB, LOW);
    digitalWrite(segmentC, LOW);
    digitalWrite(segmentD, LOW);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, LOW);
    digitalWrite(segmentG, LOW);

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
