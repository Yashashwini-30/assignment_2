#include <DHT.h>

// Pin Definitions
#define DHTPIN 2       // Pin where the DHT11 data line is connected
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const float threshold = 30.0; // Temperature threshold for warning

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  dht.begin();        // Initialize the DHT11 sensor
}

void loop() {
  delay(2000); // Wait a few seconds between measurements

  float temperature = dht.readTemperature(); // Read temperature in Celsius

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature > threshold) {
    Serial.println("Warning: Temperature exceeds threshold!");
  }
}
