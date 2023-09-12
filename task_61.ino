#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(32, 16, 2);

#define SENSOR1_PIN 2
#define SENSOR2_PIN 3

#define SELECT_PROGRAM 0
#define SETTINGS 1
#define POWER_SAVING 2
#define SHUT_DOWN 3

byte arrow[8] = {
  B11000,
  B11100,
  B11110,
  B11111,
  B11111,
  B11110,
  B11100,
  B11000
};

byte currentOption = SELECT_PROGRAM;

void setup() {
  pinMode(SENSOR1_PIN, INPUT_PULLUP);
  pinMode(SENSOR2_PIN, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  
  lcd.createChar(0, arrow);
  
  lcd.clear();
  lcd.home();
  lcd.write(0);
  lcd.print(" Select Program");
  lcd.setCursor(0, 1);
  lcd.print(" Settings ");
}

void loop() {
  bool sensor1 = !digitalRead(SENSOR1_PIN);
  bool sensor2 = !digitalRead(SENSOR2_PIN);
  
  if (sensor1) {
    currentOption++;
    if (currentOption > SHUT_DOWN) {
      currentOption = SHUT_DOWN;
    }
    while (!digitalRead(SENSOR1_PIN));
    lcd.clear();
    printOption(currentOption);
    Serial.println(currentOption);
  }
  
  else if (sensor2) {
    currentOption--;
    if (currentOption < SELECT_PROGRAM) {
      currentOption = SELECT_PROGRAM;
    }
    while (!digitalRead(SENSOR2_PIN));
    lcd.clear();
    printOption(currentOption);
    Serial.println(currentOption);
  }
  
}

void printOption(byte option) {
  switch (option) {
    case SELECT_PROGRAM:
      lcd.home();
      lcd.write(0);
      lcd.print(" Select Program");
      lcd.setCursor(0, 1);
      lcd.print(" Settings ");
      break;
    case SETTINGS:
      lcd.home();
      lcd.print(" Select Program");
      lcd.setCursor(0, 1);
      lcd.write(0);
      lcd.print(" Settings ");
      break;
    case POWER_SAVING:
      lcd.home();
      lcd.print(" Settings ");
      lcd.setCursor(0, 1);
      lcd.write(0);
      lcd.print(" Power Saving ");
      break;
    case SHUT_DOWN:
      lcd.home();
      lcd.print(" Power Saving ");
      lcd.setCursor(0, 1);
      lcd.write(0);
      lcd.print(" Shut down");
      break;
  }
  
}
