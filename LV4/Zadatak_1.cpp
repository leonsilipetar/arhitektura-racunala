//Zadatak 1.1
const int PIN_CRVENA = 3; // D3
const int PIN_ZELENA  = 4; // D4
const int PIN_PLAVA   = 5; // D5

void setup() {
  Serial.begin(9600);
  pinMode(PIN_CRVENA, INPUT_PULLUP);
  pinMode(PIN_ZELENA, INPUT_PULLUP);
  pinMode(PIN_PLAVA, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(PIN_CRVENA) == LOW) {
    Serial.println("Stisnuta tipka: CRVENA");
    delay(200);
  }
  if (digitalRead(PIN_ZELENA) == LOW) {
    Serial.println("Stisnuta tipka: ZELENA");
    delay(200);
  }
  if (digitalRead(PIN_PLAVA) == LOW) {
    Serial.println("Stisnuta tipka: PLAVA");
    delay(200);
  }
}

//Zadatak 1.2
const int TIPKA_R = 3; // D3
const int TIPKA_G = 4; // D4
const int TIPKA_B = 5; // D5

const int LED_R = 9;  // D9
const int LED_G = 10; // D10
const int LED_B = 11; // D11

void setup() {
  Serial.begin(9600);

  pinMode(TIPKA_R, INPUT_PULLUP);
  pinMode(TIPKA_G, INPUT_PULLUP);
  pinMode(TIPKA_B, INPUT_PULLUP);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
}

void loop() {
  bool rStisnuto = (digitalRead(TIPKA_R) == LOW);
  bool gStisnuto = (digitalRead(TIPKA_G) == LOW);
  bool bStisnuto = (digitalRead(TIPKA_B) == LOW);

  digitalWrite(LED_R, rStisnuto ? HIGH : LOW);
  digitalWrite(LED_G, gStisnuto ? HIGH : LOW);
  digitalWrite(LED_B, bStisnuto ? HIGH : LOW);

  if (rStisnuto) Serial.println("Crvena");
  if (gStisnuto) Serial.println("Zelena");
  if (bStisnuto) Serial.println("Plava");

  delay(50);
}