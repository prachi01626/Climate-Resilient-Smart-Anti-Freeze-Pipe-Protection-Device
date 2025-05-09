#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin setup
#define ONE_WIRE_BUS 2
#define FAN_PIN 3
#define HEATER_PIN 4

// Sensor setup
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Start serial and sensor
  Serial.begin(9600);
  sensors.begin();

  // Start LCD
  lcd.init();
  lcd.backlight();

  // Set pin modes
  pinMode(FAN_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);

  // Turn off fan and heater initially
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(HEATER_PIN, LOW);
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  // Display temperature on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print((char)223); // Degree symbol
  lcd.print("C   ");

  // Control logic
  if (tempC > 32) {
    digitalWrite(FAN_PIN, HIGH);
    digitalWrite(HEATER_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Fan ON  Heat OFF");
  }
  else if (tempC < 30) {
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(HEATER_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Fan OFF Heat ON ");
  }
  else {
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(HEATER_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Fan OFF Heat OFF");
  }

  delay(1000); // Wait 1 second before next read
}