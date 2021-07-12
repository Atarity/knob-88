#include <Arduino.h>

#define buttonPin 8
#define buttonGndPin 10
#define encoderAPin 3
#define encoderGndPin 4
#define encoderBPin 5

volatile int buttonState = 0; // volatile because will use in interruption function

volatile int encoderPos = 0;  // a counter for the dial
int lastReportedPos = 1;   // change management
static boolean rotating = false;    // debounce management

// interrupt service routine vars
boolean A_set = false;
boolean B_set = false;

void doEncoderA() {
    if ( rotating ) delay (1);  // wait a little until the bouncing is done
    if ( digitalRead(encoderAPin) != A_set ) { // debounce once more
        A_set = !A_set;
        // adjust counter + if A leads B
        if ( A_set && !B_set )
        encoderPos++;
        rotating = false;  // no more debouncing until loop() hits again
    }
}

void doEncoderB() {
    if ( rotating ) delay (1);
    if ( digitalRead(encoderBPin) != B_set ) {
        B_set = !B_set;
        //  adjust counter - 1 if B leads A
        if ( B_set && !A_set )
        encoderPos--;
        rotating = false;
    }
}

void doClick() {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
        digitalWrite(LED_BUILTIN, HIGH);
        //encoderPos = 0;
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
    attachInterrupt(digitalPinToInterrupt(encoderAPin), doEncoderA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderBPin), doEncoderB, CHANGE);

    Serial.begin (115200);
}

void loop() {
    rotating = true;  // reset the debouncer
    if (lastReportedPos != encoderPos) {
        Serial.print("Index: ");
        Serial.println(encoderPos, DEC);
        lastReportedPos = encoderPos;
    }
}
