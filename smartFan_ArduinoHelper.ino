// Arduino 2 (Helper) - Supplies Power to the Motor

void setup() {
  // Arduino 2 does not control logic, only provides power.
  pinMode(9, OUTPUT);  // Enable_B as output to pass voltage
  digitalWrite(9, HIGH); // Set to high to enable power supply
}

void loop() {
  // Continuously supply power
}
