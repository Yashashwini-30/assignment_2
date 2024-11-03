// Pin Definitions
const int irSensor1Pin = 2; // Entrance IR sensor
const int irSensor2Pin = 3; // Exit IR sensor
const int trigPin = 4;       // Ultrasonic trigger pin
const int echoPin = 5;       // Ultrasonic echo pin

// 7-Segment Display Pin Definitions
const int segmentPins[] = {6, 7, 8, 9, 10, 11, 12}; // Segments A to G

int count = 0; // People count
bool entering = false;
bool exiting = false;

void setup() {
  Serial.begin(9600);

  pinMode(irSensor1Pin, INPUT);
  pinMode(irSensor2Pin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  // Check IR sensor 1 (Entrance)
  if (digitalRead(irSensor1Pin) == HIGH) {
    delay(50); // Debounce delay
    if (digitalRead(irSensor1Pin) == HIGH) {
      entering = true; // Person detected at entrance
      delay(500); // Delay to avoid multiple triggers
    }
  }

  // Check IR sensor 2 (Exit)
  if (digitalRead(irSensor2Pin) == HIGH) {
    delay(50); // Debounce delay
    if (digitalRead(irSensor2Pin) == HIGH) {
      exiting = true; // Person detected at exit
      delay(500); // Delay to avoid multiple triggers
    }
  }

  // If a person is entering
  if (entering) {
    long duration = measureDistance();
    if (duration < 500) { // Confirm direction based on distance measurement
      count++; // Increase count for entering
      displayCount(count);
      Serial.println("Entering: " + String(count));
    }
    entering = false;
  }

  // If a person is exiting
  if (exiting) {
    long duration = measureDistance();
    if (duration < 500) { // Confirm direction based on distance measurement
      count--; // Decrease count for exiting
      displayCount(count);
      Serial.println("Exiting: " + String(count));
    }
    exiting = false;
  }
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Calculate distance in cm
}

void displayCount(int num) {
  int digits[4] = {0, 0, 0, 0}; // Adjust for your display
  if (num < 0) num = 0; // Prevent negative counts
  if (num > 9999) num = 9999; // Max count for 4-digit display

  for (int i = 3; i >= 0; i--) {
    digits[i] = num % 10;
    num /= 10;
  }

  for (int i = 0; i < 4; i++) {
    // Convert digit to 7-segment representation
    int segmentValue = getSegmentValue(digits[i]);
    for (int j = 0; j < 7; j++) {
      digitalWrite(segmentPins[j], segmentValue & (1 << j));
    }
    delay(1000); // Show each digit for a second
  }
}

int getSegmentValue(int num) {
  switch (num) {
    case 0: return 0b11111100; // 0
    case 1: return 0b01100000; // 1
    case 2: return 0b11011010; // 2
    case 3: return 0b11110010; // 3
    case 4: return 0b01100110; // 4
    case 5: return 0b10110110; // 5
    case 6: return 0b10111110; // 6
    case 7: return 0b11100000; // 7
    case 8: return 0b11111110; // 8
    case 9: return 0b11110110; // 9
    default: return 0b00000000; // Off
  }
}
