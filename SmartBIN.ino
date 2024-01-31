#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

const int trigPin = 9;
const int echoPin = 10;
const int lidControlPin = 7;
const int buzzerPin = 8;
const int ledPin = 13;

const int binFullThreshold = 30;
const int lidOpenDuration = 5000;

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial btSerial(2, 3);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lidControlPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Smart Bin");
  delay(2000);
  lcd.clear();

  btSerial.begin(9600);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");

  if (distance < binFullThreshold) {
    lcd.setCursor(0, 1);
    lcd.print("Bin Full!     ");

    digitalWrite(buzzerPin, HIGH);
    digitalWrite(lidControlPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(lidOpenDuration);

    digitalWrite(lidControlPin, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);

    btSerial.println("Bin Full! Lid opened.");

  } else {
    lcd.setCursor(0, 1);
    lcd.print("Bin Empty     ");

    digitalWrite(lidControlPin, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(1000);
}
