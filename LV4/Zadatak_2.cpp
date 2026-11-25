//Zadatak 2.1
#include <Keypad.h>

const byte ROWS = 1;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'R', 'G', 'B'}
};

// A0 (14) je zajednički pin/redak, A1 (15), A2 (16), A3 (17) su stupci
byte rowPins[ROWS] = {A0};
byte colPins[COLS] = {A1, A2, A3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.print("Stisnuta tipka: ");
    Serial.println(key);
  }
}
//Zadatak 2.2
#include <Keypad.h>

const byte ROWS = 1;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'R', 'G', 'B'}
};

byte rowPins[ROWS] = {A0};
byte colPins[COLS] = {A1, A2, A3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int LED_R = 9;
const int LED_G = 10;
const int LED_B = 11;

int valR = 0;
int valG = 0;
int valB = 0;

unsigned long lastHoldStep = 0;
const unsigned long HOLD_INTERVAL = 1000;
const int STEP_20_PCT = 51; // 20% od 255

int getLedPin(char key) {
  if (key == 'R') return LED_R;
  if (key == 'G') return LED_G;
  if (key == 'B') return LED_B;
  return -1;
}

int* getChannelPtr(char key) {
  if (key == 'R') return &valR;
  if (key == 'G') return &valG;
  if (key == 'B') return &valB;
  return nullptr;
}

void keypadEvent(KeypadEvent key) {
  KeyState state = keypad.getState();
  int pin = getLedPin(key);
  int* ch = getChannelPtr(key);
  if (pin < 0 || ch == nullptr) return;

  if (state == PRESSED) {
    if (*ch == 0) {
      *ch = STEP_20_PCT;
      analogWrite(pin, *ch);
    }
    lastHoldStep = millis();
    Serial.print(key);
    Serial.print(" PRESSED -> PWM: ");
    Serial.println(*ch);
  } else if (state == HOLD) {
    if (millis() - lastHoldStep >= HOLD_INTERVAL) {
      lastHoldStep = millis();
      *ch = min(255, *ch + STEP_20_PCT);
      analogWrite(pin, *ch);
      Serial.print(key);
      Serial.print(" HOLD (+20%) -> PWM: ");
      Serial.println(*ch);
    }
  } else if (state == RELEASED) {
    *ch = 0;
    analogWrite(pin, 0);
    Serial.print(key);
    Serial.println(" RELEASED -> PWM: 0");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  keypad.setHoldTime(300);
  keypad.addEventListener(keypadEvent);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.print("Tipka: ");
    Serial.println(key);
  }
}