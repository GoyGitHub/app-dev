// =======================================
// Libraries
// =======================================

#include <Wire.h>                 // Enables I2C communication protocol (used by the LCD)
#include <LiquidCrystal_I2C.h>    // Library to control I2C LCD
#include <DHT.h>                  // Library to read data from the DHT temperature & humidity sensor

// =======================================
// LCD Setup
// =======================================

LiquidCrystal_I2C lcd(0x27, 16, 2); 
// Creates an LCD object with:
// 0x27 -> I2C address of the LCD module
// 16   -> Number of columns (characters per line)
// 2    -> Number of rows

// =======================================
// DHT Sensor Setup
// =======================================

#define DHTPIN A3        // Defines the analog pin (A3) where the DHT11 sensor data pin is connected
#define DHTTYPE DHT11    // Specifies the type of DHT sensor being used (DHT11)
DHT dht(DHTPIN, DHTTYPE); 
// Creates a DHT object using the defined pin and sensor type

// =======================================
// Variables
// =======================================

int h;  // Stores the humidity value
int t;  // Stores the temperature value

// =======================================
// Setup Function
// Runs once when the Arduino starts or resets
// =======================================

void setup() {
  Serial.begin(9600);  
  // Starts serial communication at 9600 baud rate
  // This allows sending temperature and humidity data to the Serial Monitor

  Serial.println("Temperature and Humidity Sensor Test");  
  // Prints a message to indicate the program has started

  dht.begin();  
  // Initializes the DHT sensor so it can start reading data

  lcd.init();        
  // Initializes the LCD display

  lcd.backlight();   
  // Turns on the LCD backlight so text is visible
}

// =======================================
// Main Loop
// Repeats continuously after setup()
// =======================================

void loop() {
  // === Reading Sensor Values ===
  h = dht.readHumidity();       // Reads the current humidity from the DHT11 sensor
  t = dht.readTemperature();    // Reads the current temperature (in Celsius) from the DHT11 sensor

  // === Sending Data to Serial Monitor ===
  Serial.print("Humidity: ");   // Prints label for humidity
  Serial.print(h);              // Prints the actual humidity value
  Serial.print(" %, Temp: ");   // Prints label for temperature
  Serial.print(t);              // Prints the actual temperature value
  Serial.println(" °C");        // Prints "°C" and moves to the next line

  // === Displaying Data on LCD ===
  lcd.setCursor(0, 0);          // Sets the cursor to the first row, first column
  lcd.print("Temperature:");    // Prints the label "Temperature:"
  lcd.print(t);                  // Prints the temperature value
  lcd.print("C");                // Prints "C" for Celsius

  lcd.setCursor(0, 1);          // Sets the cursor to the second row, first column
  lcd.print("Humidity:");       // Prints the label "Humidity:"
  lcd.print(h);                  // Prints the humidity value
  lcd.print("%");                // Prints "%" for percentage

  // === Delay Before Next Update ===
  delay(1000);                   // Waits 1 second before taking the next reading
}
