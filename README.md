# Arduino Fan Control with LEDs and Potentiometer

---

## Project Overview

This project uses two Arduino boards to control the speed of a DC fan using a potentiometer. Three LEDs indicate different speed ranges: red for slow, green for medium, and blue for fast. The serial monitor displays the potentiometer value, motor speed, and LED status.

---

## Components

- **Arduino Main (Arduino 1)** - Controls the LEDs, potentiometer, and L293D motor driver.
- **Arduino Helper (Arduino 2)** - Powers the DC motor through a transistor and diode setup.
- **DC Motor with Fan Blade** - Controlled via PWM.
- **10K Potentiometer** - Adjusts motor speed.
- **L293D Motor Driver** - Controls the motor direction and speed.
- **2N2222 Transistor** - Boosts current to the motor.
- **1N4007 Diode** - Protects against back EMF.
- **3 LEDs (Red, Green, Blue)** - Indicates speed ranges.
- **9V Battery with Barrel Connector** - Powers Arduino Helper (replaced with USB connection for stability).
- **220-ohm Resistors** - For LEDs.
- **Breadboard and Jumper Wires** - For connections.

---

## Wiring Diagram

### Arduino Main (Arduino 1):

| Component             | Pin Connection                                      | Wire Color |
| --------------------- | --------------------------------------------------- | ---------- |
| Potentiometer         | Pin 1 - A0, Pin 2 - +5V, Pin 3 - GND                | Red, Black |
| Red LED               | Pin 2 (Long end) & (Short end) 220Ω Resistor to GND | Orange     |
| Blue LED              | Pin 3 (Long end) & (Short end) 220Ω Resistor to GND | Orange     |
| Green LED             | Pin 4 (Long end) & (Short end) 220Ω Resistor to GND | Orange     |
| L293D Enable A        | Pin 9                                               | Green      |
| L293D Input 1         | Pin 8                                               | Blue       |
| L293D Input 2         | Pin 7                                               | Blue       |
| L293D VCC1            | +5V                                                 | Red        |
| L293D VCC2            | +5V (via Arduino 2) - VIN                           | Red        |
| L293D GND (4,5,12,13) | GND                                                 | Black      |

### Arduino Helper (Arduino 2):

| Component       | Pin Connection                 | Wire Color |
| --------------- | ------------------------------ | ---------- |
| DC Motor (+)    | Collector of 2N2222 Transistor | Black      |
| DC Motor (-)    | Emitter of 2N2222 Transistor   | Black      |
| Transistor Base | 1K Resistor to L293D Output 1  | White      |
| Diode Cathode   | Positive terminal of DC Motor  | N/A        |
| Diode Anode     | Negative terminal of DC Motor  | N/A        |
| Arduino VIN     | L293D VCC2                     | Red        |
| Arduino GND     | Common GND with Arduino Main   | Black      |

---

## Code

### Arduino 1 (Main Controller)

```cpp
int potPin = A0;
int redLED = 2;
int blueLED = 3;
int greenLED = 4;
int enA = 9;
int in1 = 8;
int in2 = 7;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int motorSpeed = map(potValue, 0, 1023, 0, 255);
  analogWrite(enA, motorSpeed);

  if (motorSpeed == 0) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    Serial.println("Motor OFF");
  } else if (motorSpeed <= 64) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    Serial.print("Red LED ON. Pot Value: ");
    Serial.print(potValue);
    Serial.print(" Motor Speed: ");
    Serial.println(motorSpeed);
  } else if (motorSpeed <= 191) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, LOW);
    Serial.print("Green LED ON. Pot Value: ");
    Serial.print(potValue);
    Serial.print(" Motor Speed: ");
    Serial.println(motorSpeed);
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
    Serial.print("Blue LED ON. Pot Value: ");
    Serial.print(potValue);
    Serial.print(" Motor Speed: ");
    Serial.println(motorSpeed);
  }
  delay(100);
}
```

### Arduino 2 (Helper Source)

```cpp
void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  analogWrite(9, 255); // Full speed signal to L293D Enable B
}
```

---

## Issues Faced

- Insufficient current to the motor caused low-speed performance.
- Voltage drop from the 9V battery reduced power output.
- Potentiometer wiring was initially reversed.
- L293D outputs did not provide adequate voltage to the motor.

---

## Suggestions for Improvements

- Use a **12V Power Supply** for Arduino Helper to increase motor performance.
- Add a **Dedicated Motor Driver Module (e.g., L298N)** for higher power handling.
- Replace the **2N2222 Transistor** with a **MOSFET (e.g., IRF540N)** for better efficiency.
- Optimize wiring to reduce resistance and voltage drops.
- Consider using a **DC-DC Boost Converter** for regulated motor voltage.

---

## Final Notes

This project demonstrates the control of a fan using Arduino and provides visual feedback with LEDs for different speed ranges. While functional, improvements in power management are suggested for better performance.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

