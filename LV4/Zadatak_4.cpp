//Zadatak 4.1 i 4.2
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

const int LED_SEF = 13;
const int BUZZER_PIN = 6;

const char CORRECT_PIN[5] = "1234";
char enteredPin[5] = "";
byte pinIndex = 0;
bool resetTriggeredOnHold = false;

void resetEntry(const char* reason) {
  pinIndex = 0;
  enteredPin[0] = '\0';
  digitalWrite(LED_SEF, LOW);
  noTone(BUZZER_PIN);
  Serial.print("Reset postupka: ");
  Serial.println(reason);
}

void playUnlockMelody() {
  int notes[] = {523, 659, 784, 1046};
  int durations[] = {140, 140, 140, 280};

  for (int i = 0; i < 4; i++) {
    tone(BUZZER_PIN, notes[i], durations[i]);
    delay(durations[i] + 40);
  }
  noTone(BUZZER_PIN);
}

void keypadEvent(KeypadEvent key) {
  if (keypad.getState() == HOLD) {
    resetTriggeredOnHold = true;
    resetEntry("dugo drzanje tipke (HOLD)");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_SEF, OUTPUT);
  digitalWrite(LED_SEF, LOW);
  pinMode(BUZZER_PIN, OUTPUT);

  keypad.setHoldTime(1000); // 1 sekunda za reset
  keypad.addEventListener(keypadEvent);

  Serial.println("Digitalni sef spreman. Upisite 4 znamenke PIN-a:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (resetTriggeredOnHold) {
      resetTriggeredOnHold = false;
      return;
    }

    tone(BUZZER_PIN, 800, 70);
    enteredPin[pinIndex] = key;
    pinIndex++;
    enteredPin[pinIndex] = '\0';

    Serial.print("Uneseno znamenki: ");
    Serial.println(pinIndex);

    if (pinIndex == 4) {
      if (strcmp(enteredPin, CORRECT_PIN) == 0) {
        Serial.println("PIN TOCAN! Sef otkljucan.");
        digitalWrite(LED_SEF, HIGH);
        playUnlockMelody();
      } else {
        Serial.println("POGRESAN PIN! Pokusajte ponovno.");
        digitalWrite(LED_SEF, LOW);
        tone(BUZZER_PIN, 220, 350);
        delay(400);
        noTone(BUZZER_PIN);
      }

      pinIndex = 0;
      enteredPin[0] = '\0';
    }
  }
}