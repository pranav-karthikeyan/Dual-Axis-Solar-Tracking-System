// Solar panel efficiency simulation
// Dual axis servo motor control
// Team Members: Krisshanth, Praveen and Pranav

#define BLYNK_TEMPLATE_ID "TMPL30Uk-g0Y2"
#define BLYNK_TEMPLATE_NAME "Solar tracking system"
#define BLYNK_AUTH_TOKEN "jZE-TmHnuf1HbfnyDwqm-HbhpZK0tz_Y"

#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA219.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create I2C objects
TwoWire I2C_OLED = TwoWire(0);
TwoWire I2C_INA = TwoWire(1);

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2C_OLED, -1);

// Create INA219 sensor object
Adafruit_INA219 ina219(0x40);

// Create servo objects
Servo azimuthServo;
Servo elevationServo;

// Define LDR pins
const int ldrPinTop = 32;
const int ldrPinBottom = 33;
const int ldrPinLeft = 34;
const int ldrPinRight = 35;

// Define servo pins
const int azimuthServoPin = 13;
const int elevationServoPin = 12;

// WiFi credentials
const char *ssid = "Pranavs M35";
const char *password = "morris mano";

// Blynk Timer
BlynkTimer timer;

// Servo position tracking
int azimuthPos = 90;
int elevationPos = 90;

bool isCalibrating = false;
unsigned long lastCalibrationTime = 0;
const unsigned long calibrationMessageDuration = 2000;
const int threshold = 50;

void sendSensorData() {
    float voltage = ina219.getBusVoltage_V();
    float current = abs(ina219.getCurrent_mA());
    float power = abs(voltage * (current));

    Blynk.virtualWrite(V0, voltage);
    Blynk.virtualWrite(V1, current);
    Blynk.virtualWrite(V2, power);
}

void setup() {
    Serial.begin(115200);

    azimuthServo.attach(azimuthServoPin);
    elevationServo.attach(elevationServoPin);
    azimuthServo.write(azimuthPos);
    elevationServo.write(elevationPos);

    pinMode(ldrPinTop, INPUT);
    pinMode(ldrPinBottom, INPUT);
    pinMode(ldrPinLeft, INPUT);
    pinMode(ldrPinRight, INPUT);

    I2C_OLED.begin(21, 22, 400000);
    I2C_INA.begin(25, 26, 400000);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (1);
    }

    if (!ina219.begin(&I2C_INA)) {
        Serial.println(F("Failed to find INA219 chip"));
        while (1);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Initializing...");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.display();

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(1000);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect. Restarting...");
        ESP.restart();
    }

    Blynk.config(BLYNK_AUTH_TOKEN);
    Blynk.connect();
    timer.setInterval(5000L, sendSensorData);
}

void loop() {
    int ldrValueTop = analogRead(ldrPinTop);
    int ldrValueBottom = analogRead(ldrPinBottom);
    int ldrValueLeft = analogRead(ldrPinLeft);
    int ldrValueRight = analogRead(ldrPinRight);

    Serial.print("Top: "); Serial.print(ldrValueTop);
    Serial.print("  Bottom: "); Serial.print(ldrValueBottom);
    Serial.print("  Left: "); Serial.print(ldrValueLeft);
    Serial.print("  Right: "); Serial.println(ldrValueRight);

    int verticalDifference = ldrValueTop - ldrValueBottom;
    int horizontalDifference = ldrValueLeft - ldrValueRight;

    float voltage = ina219.getBusVoltage_V();
    float current = abs(ina219.getCurrent_mA());
    float power = abs(voltage * current);

    String displayMessage = "Calibrated";
    isCalibrating = false;

    if (verticalDifference > threshold) {
        elevationPos = min(elevationPos + 1, 130);
        displayMessage = "Top";
        isCalibrating = true;
    } else if (verticalDifference < -threshold) {
        elevationPos = max(elevationPos - 1, 0);
        displayMessage = "Bottom";
        isCalibrating = true;
    }

    if (horizontalDifference > threshold) {
        azimuthPos = min(azimuthPos + 1, 180);
        displayMessage = "Right";
        isCalibrating = true;
    } else if (horizontalDifference < -threshold) {
        azimuthPos = max(azimuthPos - 1, 0);
        displayMessage = "Left";
        isCalibrating = true;
    }

    if (isCalibrating) {
        azimuthServo.write(azimuthPos);
        elevationServo.write(elevationPos);
        lastCalibrationTime = millis();
        Serial.println("Calibration in progress...");
    }

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(displayMessage);
    display.setCursor(0, 16);
    display.print("Voltage: "); display.print(voltage, 2); display.print("V");
    display.setCursor(0, 32);
    display.print("Current: "); display.print(current, 2); display.print("mA");
    display.setCursor(0, 48);
    display.print("Power: "); display.print(power, 2); display.print("mW");
    display.display();

    // Send LDR status to Blynk label V3
    Blynk.virtualWrite(V3, displayMessage);

    Blynk.run();
    timer.run();
    delay(50);
}
