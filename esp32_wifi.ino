/* ==========================================================================
   ESP32 Parcel Box - WiFi Web Server Version (Run from Anywhere / Any Phone)
   --------------------------------------------------------------------------
   This sketch turns your ESP32 into a standalone WiFi server or connects it 
   to your local WiFi network. 
   
   Allows you to unlock the parcel box from ANY smartphone or browser on the 
   network WITHOUT requiring a USB cable or Web Serial!
   
   Wiring:
     - SG90 Signal (Orange) -> GPIO 4
     - SG90 VCC    (Red)    -> 5V / VIN
     - SG90 GND    (Brown)  -> GND
   ========================================================================== */

#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// Enter your WiFi credentials (or leave as Access Point mode below)
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

const int SERVO_PIN = 4;
const int ANGLE_LOCKED = 0;
const int ANGLE_UNLOCKED = 90;

Servo boxServo;
WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "ESP32 Parcel Box Server Online");
}

void handleUnlock() {
  boxServo.write(ANGLE_UNLOCKED);
  delay(350);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ACK: UNLOCKED (90 deg)");
}

void handleLock() {
  boxServo.write(ANGLE_LOCKED);
  delay(350);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ACK: LOCKED (0 deg)");
}

void setup() {
  Serial.begin(115200);
  
  // Initialize Servo on GPIO 4
  ESP32PWM::allocateTimer(0);
  boxServo.setPeriodHertz(50);
  boxServo.attach(SERVO_PIN, 500, 2400);
  boxServo.write(ANGLE_LOCKED); // Default locked

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // API Endpoints
  server.on("/", handleRoot);
  server.on("/unlock", handleUnlock);
  server.on("/lock", handleLock);

  server.begin();
  Serial.println("HTTP Server started");
}

void loop() {
  server.handleClient();
}
