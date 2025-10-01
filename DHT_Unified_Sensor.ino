#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <math.h>  // For log() and exp()

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN A3        
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);

float h;   // humidity
float t;   // temperature
float dp;  // dew point
float rh;  // recomputed relative humidity
float hi;  // heat index

void setup() {
  Serial.begin(9600);
  Serial.println("Temperature and Humidity Sensor Test");

  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  // === Reading sensor values (floats for decimal precision) ===
  h = dht.readHumidity();
  t = dht.readTemperature();

  // === Compute dew point using Magnus formula ===
  float gamma = (17.625 * t) / (243.04 + t) + log(h / 100.0);
  dp = (243.04 * gamma) / (17.625 - gamma);

  // === Recompute RH using given formula ===
  float rh_top = exp((17.625 * dp) / (243.04 + dp));
  float rh_bottom = exp((17.625 * t) / (243.04 + t));
  rh = 100.0 * (rh_top / rh_bottom);

  // === Compute Heat Index (feels-like temperature) ===
  hi = dht.computeHeatIndex(t, h, false);  // false = Celsius

  // === Serial output ===
  Serial.print("Temp: ");
  Serial.print(t, 1);
  Serial.print(" °C, Humidity: ");
  Serial.print(h, 1);
  Serial.print(" %, Dew Point: ");
  Serial.print(dp, 1);
  Serial.print(" °C, Recalc RH: ");
  Serial.print(rh, 1);
  Serial.print(" %, Heat Index: ");
  Serial.print(hi, 1);
  Serial.println(" °C");

  // === LCD output (TEMP + HUMIDITY only) ===
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(t, 1);
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("Humid:");
  lcd.print(h, 1);
  lcd.print("%");

  delay(2000);
}
