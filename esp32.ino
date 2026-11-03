/* ==========================================================================
   ESP32 Smart Parcel Box Controller Firmware
   --------------------------------------------------------------------------
   Hardware:
     - ESP32 Development Board (NodeMCU / DevKit v1)
     - SG90 Micro Servo (or compatible 5V servo)
       * Signal (Orange/Yellow) -> GPIO 4
       * Power  (Red)         .-  -> 5V / VIN (or external 5V regulator)
       * Ground (Brown/Black)   -> GND
       
   Baud Rate: 9600 baud
   Command Protocol:
     - "1\n" : Rotate servo to 0 degrees  (UNLOCK box)
     - "0\n" : Rotate servo to 90 degrees (LOCK box)
     
   Library Requirement:
     - "ESP32Servo" by Kevin Harrington (Install via Arduino Library Manager)
     - Note: Do NOT use the default Arduino "Servo.h" as it is incompatible 
             with ESP32 hardware timers.
   ========================================================================== */

#include <ESP32Servo.h>

// Pin definition for SG90 servo PWM signal
const int SERVO_PIN = 4;

// Standard SG90 pulse-width timings (microseconds)
const int SERVO_MIN_PULSE = 500;   // Minimum pulse width
const int SERVO_MAX_PULSE = 2400;  // Maximum pulse width

// Physical angles configured for motor latch setup:
// 0 deg  = Latch open / retracted (UNLOCKED)
// 90 deg = Latch engaged / closed (LOCKED)
const int ANGLE_UNLOCKED = 0;   // 0 deg  = Box Unlocked
const int ANGLE_LOCKED   = 90;  // 90 deg = Box Locked

Servo boxServo;
int currentAngle = ANGLE_LOCKED;

void setup() {
  // Initialize Serial communication at 9600 baud
  Serial.begin(9600);
  delay(1000);

  // Allocate hardware timers for ESP32PWM
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Standard 50Hz frequency for analog servos
  boxServo.setPeriodHertz(50);
  
  // Attach servo to GPIO 4 with pulse range
  boxServo.attach(SERVO_PIN, SERVO_MIN_PULSE, SERVO_MAX_PULSE);

  // Set default initial state to LOCKED (90 degrees)
  boxServo.write(ANGLE_LOCKED);
  currentAngle = ANGLE_LOCKED;

  // Send startup banner and status
  Serial.println();
  Serial.println(F("=========================================="));
  Serial.println(F("[ESP32] Smart Parcel Box Controller Initialized"));
  Serial.println(F("[ESP32] Baud Rate: 9600 | Servo Pin: GPIO 4"));
  Serial.println(F("[ESP32] ACK: LOCKED (90 deg)"));
  Serial.println(F("=========================================="));
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "1") {
      // Command '1': Unlock box (rotates to 0 degrees)
      boxServo.write(ANGLE_UNLOCKED);
      currentAngle = ANGLE_UNLOCKED;
      delay(350);
      Serial.println(F("[ESP32] ACK: UNLOCKED (0 deg)"));
    } 
    else if (command == "0") {
      // Command '0': Lock box (rotates to 90 degrees)
      boxServo.write(ANGLE_LOCKED);
      currentAngle = ANGLE_LOCKED;
      delay(350);
      Serial.println(F("[ESP32] ACK: LOCKED (90 deg)"));
    } 
    else if (command.length() > 0) {
      Serial.print(F("[ESP32] WARN: Unknown command '"));
      Serial.print(command);
      Serial.println(F("'. Send '1' to unlock (0 deg) or '0' to lock (90 deg)."));
    }
  }
}
