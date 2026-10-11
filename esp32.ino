/* ==========================================================================
   ESP32 Parcel Box Controller Firmware
   --------------------------------------------------------------------------
   Hardware:
     - ESP32 Development Board (NodeMCU / DevKit v1)
     - SG90 Micro Servo (or compatible 5V servo)
       * Signal (Orange/Yellow) -> GPIO 4
       * Power  (Red)           -> 5V / VIN (or external 5V regulator)
       * Ground (Brown/Black)   -> GND
       
   Baud Rate: 9600 baud
   Command Protocol:
     - "1\n" : Rotate servo to 90 degrees (UNLOCK box)
     - "0\n" : Rotate servo to 0 degrees  (LOCK box)
     
   Library Requirement:
     - "ESP32Servo" by Kevin Harrington (Install via Arduino Library Manager)
     - Note: Do NOT use the default Arduino "Servo.h" as it is incompatible 
             with ESP32 hardware timers.
   ========================================================================== */

#include <ESP32Servo.h>

// Pin definition for SG90 servo PWM signal
const int SERVO_PIN = 4;

// Standard SG90 pulse-width timings (microseconds)
const int MIN_PULSE_WIDTH = 500;  // 0 degrees
const int MAX_PULSE_WIDTH = 2400; // 180 degrees

// Angles for lock mechanism
const int ANGLE_LOCKED = 0;    // 0 deg = Bolt engaged (Box Locked)
const int ANGLE_UNLOCKED = 90; // 90 deg = Bolt retracted (Box Unlocked)

Servo boxServo;
int currentAngle = ANGLE_LOCKED;

void setup() {
  // Initialize Serial communication at 9600 baud
  Serial.begin(9600);
  
  // Allow time for Serial port to stabilize
  delay(1000);

  // Allocate hardware timers for ESP32PWM
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Standard 50Hz frequency for analog servos like SG90
  boxServo.setPeriodHertz(50);
  
  // Attach servo to pin with appropriate pulse-width range
  boxServo.attach(SERVO_PIN, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);

  // Set default initial state to LOCKED (0 degrees)
  boxServo.write(ANGLE_LOCKED);
  currentAngle = ANGLE_LOCKED;

  // Send startup banner and status
  Serial.println();
  Serial.println(F("=========================================="));
  Serial.println(F("[ESP32] Smart Parcel Box Controller Initialized"));
  Serial.println(F("[ESP32] Baud Rate: 9600 | Servo Pin: GPIO 4"));
  Serial.println(F("[ESP32] ACK: LOCKED (0 deg)"));
  Serial.println(F("=========================================="));
}

void loop() {
  // Check if serial data is available
  if (Serial.available() > 0) {
    // Read command until newline character
    String command = Serial.readStringUntil('\n');
    command.trim(); // Strip carriage returns, tabs, and spaces

    // Process valid commands
    if (command == "1") {
      // Command '1': Unlock box (90 degrees)
      boxServo.write(ANGLE_UNLOCKED);
      currentAngle = ANGLE_UNLOCKED;
      
      // Delay to ensure physical movement completes before reporting ACK
      delay(350);
      
      Serial.println(F("[ESP32] ACK: UNLOCKED (90 deg)"));
    } 
    else if (command == "0") {
      // Command '0': Lock box (0 degrees)
      boxServo.write(ANGLE_LOCKED);
      currentAngle = ANGLE_LOCKED;
      
      // Delay to ensure physical movement completes before reporting ACK
      delay(350);
      
      Serial.println(F("[ESP32] ACK: LOCKED (0 deg)"));
    } 
    else if (command.length() > 0) {
      // Command received was not '1' or '0'
      Serial.print(F("[ESP32] WARN: Unknown command '"));
      Serial.print(command);
      Serial.println(F("'. Send '1' to unlock or '0' to lock."));
    }
  }
}
