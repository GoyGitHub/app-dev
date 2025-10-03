#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic pins
#define trigPin A0
#define echoPin A1

// LED pins (all red LEDs in sync)
#define led1 8
#define led2 7
#define led3 13

float distanceCm;
float distanceInch;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Andrew Gwapo");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Range:");
  lcd.setCursor(0, 1);
  lcd.print("Range:");

  Serial.begin(9600); // ✅ Serial for Python
}

void loop() {
  long duration;

  // Trigger ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = (duration / 2.0) / 29.1;
  distanceInch = distanceCm / 2.54;

  // --- Display on LCD ---
  // Clear previous number + unit (up to 7 chars: "00.00 cm")
  lcd.setCursor(7, 0);
  lcd.print("       ");
  lcd.setCursor(7, 0);
  lcd.print(distanceCm, 2);
  lcd.print("cm");

  lcd.setCursor(7, 1);
  lcd.print("       ");
  lcd.setCursor(7, 1);
  lcd.print(distanceInch, 2);
  lcd.print("in");

  // ✅ Send only the number (no "cm") for Python GUI
  Serial.println(distanceCm, 2);

  // LED blink speed depends on distance
  if (distanceCm > 10) {
    blinkAll(600);  // slow blink
  }
  else if (distanceCm <= 10 && distanceCm > 6) {
    blinkAll(400);  // medium blink
  }
  else if (distanceCm <= 6 && distanceCm >= 4) {
    blinkAll(200);  // fast blink
  }
  else if (distanceCm < 4 && distanceCm >= 1) {
    blinkAll(100);  // rapid blink
  }
  else {
    // Out of range → all OFF
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

  delay(50);
}

// Helper: blink all LEDs together in sync
void blinkAll(int interval) {
  static unsigned long lastTime = 0;
  static bool state = false;

  if (millis() - lastTime >= interval) {
    state = !state;
    digitalWrite(led1, state);
    digitalWrite(led2, state);
    digitalWrite(led3, state);
    lastTime = millis();
  }
}
