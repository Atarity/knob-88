#include <Arduino.h>

#define buttonPin 8
#define buttonGndPin 10
#define encoderAPin 3
#define encoderGndPin 4
#define encoderBPin 5

volatile int buttonState = 0; // volatile because will use in interruption function

//int encoderAPinLast = LOW;
//int encoderPos = 0;
//int enc_data = LOW;

volatile unsigned long threshold = 10000;
volatile long rotaryHalfSteps = 0;

volatile unsigned long int0time = 0;
volatile unsigned long int1time = 0;
volatile uint8_t int0signal = 0;
volatile uint8_t int1signal = 0;
volatile uint8_t int0history = 0;
volatile uint8_t int1history = 0;

void int0()
{
    if ( micros() - int0time < threshold )
        return;
    int0history = int0signal;
    int0signal = bitRead(encoderBPin, 2);

    if ( int0history == int0signal )
        return;
    int0time = micros();

    if ( int0signal == int1signal ) {
        rotaryHalfSteps++;
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        rotaryHalfSteps--;
        digitalWrite(LED_BUILTIN, LOW);
    }
    Serial.println(rotaryHalfSteps);
}

void int1()
{
    if ( micros() - int1time < threshold )
        return;
    int1history = int1signal;
    int1signal = bitRead(encoderBPin, 3);
    if ( int1history == int1signal )
        return;
    int1time = micros();
    Serial.println(rotaryHalfSteps);
}

void doClick() {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
}

// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    // encoder button setup
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(buttonGndPin, OUTPUT);
    digitalWrite(buttonGndPin, LOW);   // setting pin to GND
    attachInterrupt(digitalPinToInterrupt(buttonPin), doClick, CHANGE);  // Button click on interrupt 8

    // encoder data pins setup
    pinMode(encoderAPin, INPUT_PULLUP);
    pinMode(encoderBPin, INPUT_PULLUP);
    digitalWrite(encoderAPin, HIGH);
    digitalWrite(encoderBPin, HIGH);
    pinMode(encoderGndPin, OUTPUT);
    digitalWrite(encoderGndPin, LOW);
    attachInterrupt(digitalPinToInterrupt(encoderAPin), int0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderBPin), int1, CHANGE);

    Serial.begin (9600);
}

void loop() {
    long actualRotaryTicks = (rotaryHalfSteps / 2);
    //Serial.println(actualRotaryTicks);
    //delay(1000);
}
