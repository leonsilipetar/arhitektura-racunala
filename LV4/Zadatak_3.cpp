//Zadatak 3.1
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {7, 8, 9, 10};
byte colPins[COLS] = {13, 11, 12};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
}

//Zadatak 3.2
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {7, 8, 9, 10};
byte colPins[COLS] = {13, 11, 12};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int BUZZER_PIN = 6;

int getFreqForKey(char key) {
  switch (key) {
    case '1': return 262; // C4
    case '2': return 294; // D4
    case '3': return 330; // E4
    case '4': return 349; // F4
    case '5': return 392; // G4
    case '6': return 440; // A4
    case '7': return 494; // B4
    case '8': return 523; // C5
    case '9': return 587; // D5
    case '*': return 659; // E5
    case '0': return 698; // F5
    case '#': return 784; // G5
    default:  return 0;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.print("Tipka: ");
    Serial.println(key);
    int freq = getFreqForKey(key);
    if (freq > 0) {
      tone(BUZZER_PIN, freq, 180);
    }
  }
}