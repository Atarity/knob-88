#include <Arduino.h>

#define buttonPin 8
#define buttonGndPin 10
#define encoderClkPin 3
#define encoderGndPin 4
#define encoderDataPin 5

volatile int buttonState = 0; // volatile because will use in interruption function
int encoderClkPinLast = LOW;
int encoderPos = 0;
int enc_data = LOW;

void doClick(); // should be declared before using in setup()

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  // encoder button setup
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonGndPin, OUTPUT);
  digitalWrite(buttonGndPin, LOW);   // setting pin to GND
  attachInterrupt(digitalPinToInterrupt(buttonPin), doClick, CHANGE);  // Button click on interrupt 8

  // encoder data pins setup
  pinMode(encoderClkPin, INPUT_PULLUP);
  pinMode(encoderDataPin, INPUT_PULLUP);
  pinMode(encoderGndPin, OUTPUT);
  digitalWrite(encoderGndPin, LOW);

  Serial.begin (115200);
}

void loop() {
  // encoder section
  enc_data = digitalRead(encoderClkPin);
  if ((encoderClkPinLast == LOW) && (enc_data == HIGH)) {
    if (digitalRead(encoderDataPin) == LOW) {
      encoderPos--;
    } else {
      encoderPos++;
    }
    Serial.println (encoderPos);
  }
  encoderClkPinLast = enc_data;
}

void doClick() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}