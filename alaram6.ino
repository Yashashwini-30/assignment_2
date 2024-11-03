// Pin Definitions
const int pirPin = 2;   // PIR motion sensor OUT pin
const int buzzerPin = 3; // Buzzer pin

void setup() {
  Serial.begin(9600);     // Initialize Serial Monitor
  pinMode(pirPin, INPUT); // Set PIR pin as input
  pinMode(buzzerPin, OUTPUT); // Set Buzzer pin as output
}

void loop() {
  int motionDetected = digitalRead(pirPin); // Read the state of the PIR sensor

  if (motionDetected == HIGH) { // If motion is detected
    Serial.print("Motion detected at: "); // Log message
    Serial.println(millis()); // Log the timestamp
    tone(buzzerPin, 1000); // Sound the buzzer at 1000 Hz
    delay(1000); // Keep the buzzer on for 1 second
    noTone(buzzerPin); // Turn off the buzzer
  }

  delay(200); // Delay to avoid multiple triggers
}
