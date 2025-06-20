#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

// =================== LCD SETUP ===================
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C umumnya 0x27

// =================== Keypad SETUP ===================
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 14, 27}; // R1-R4
byte colPins[COLS] = {26, 25, 33, 32}; // C1-C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// =================== Servo SETUP ===================
Servo myServo;
int servoPin = 4;

// =================== LED & BUZZER ===================
int greenLED = 18;
int redLED   = 5;
int buzzer   = 15;

// =================== PIN SETUP ===================
String password = "2121";
String input = "";

void setup() {
  Serial.begin(9600);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ETT PINNYA DULU:");

  // Servo
  myServo.attach(servoPin);
  myServo.write(0); // posisi terkunci

  // LED & Buzzer
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      checkPassword();
    } else if (key == '*') {
      input = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ETT PINNYA DULU:");
    } else {
      if (input.length() < 4) {
        input += key;
        lcd.setCursor(6, 1);
        lcd.print(input);
      }
    }
  }
}

void checkPassword() {
  if (input == password) {
    accessGranted();
  } else {
    accessDenied();
  }
  input = "";
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ETT PINNYA DULU:");
}

void accessGranted() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Siap Boss Dibuka");
  digitalWrite(greenLED, HIGH);
  myServo.write(90); // buka
  delay(3000);
  myServo.write(0); // kunci lagi
  digitalWrite(greenLED, LOW);
}

void accessDenied() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Lu Siapa??   ");
  digitalWrite(redLED, HIGH);
  tone(buzzer, 1000); // bunyikan buzzer
  delay(1000);
  noTone(buzzer);
  digitalWrite(redLED, LOW);
}