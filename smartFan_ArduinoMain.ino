// Arduino 1 (Main) - Controls LEDs, Potentiometer, and L293D

// Pin Definitions
const int potPin = A0;          // Potentiometer pin
const int redLED = 2;          // Red LED pin
const int greenLED = 3;        // Green LED pin
const int blueLED = 4;         // Blue LED pin
const int enablePin = 9;       // L293D Enable pin
const int input1 = 8;          // L293D Input 1
const int input2 = 7;          // L293D Input 2

// Variables
int potValue = 0;              // Potentiometer value
int motorSpeed = 0;            // Motor speed (PWM value)

void setup() {
  // Initialize pins
  pinMode(potPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);

  // Start serial communication
  Serial.begin(9600);

  // Initialize motor direction (forward)
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
}

void loop() {
  // Read potentiometer value (0-1023)
  potValue = analogRead(potPin);

  // Map potentiometer value to motor speed (0-255)
  motorSpeed = map(potValue, 0, 1023, 0, 255);

  // Update motor speed
  analogWrite(enablePin, motorSpeed);

  // Determine LED and motor status
  if (motorSpeed == 0) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    Serial.println("Motor Off");
  } else if (motorSpeed > 0 && motorSpeed <= 63) { // 0 to 1/4
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    Serial.print("Red LED ON, Pot Value: ");
    Serial.print(potValue);
    Serial.print(", Motor Speed: ");
    Serial.println(motorSpeed);
  } else if (motorSpeed > 63 && motorSpeed <= 191) { // 1/4 to 3/4
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, LOW);
    Serial.print("Green LED ON, Pot Value: ");
    Serial.print(potValue);
    Serial.print(", Motor Speed: ");
    Serial.println(motorSpeed);
  } else { // 3/4 to full
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
    Serial.print("Blue LED ON, Pot Value: ");
    Serial.print(potValue);
    Serial.print(", Motor Speed: ");
    Serial.println(motorSpeed);
  }

  // Small delay for stability
  delay(100);
}

