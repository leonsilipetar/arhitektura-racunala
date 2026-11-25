//Zadatak 5.1
const int TRIG_PIN = 2; // D2
const int ECHO_PIN = 3; // D3

float measureDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30 ms (~5 m)
  if (duration == 0) return -1.0;

  // Brzina zvuka ~0.0343 cm/us; dijeli se s 2 zbog odlaska i povratka
  return (duration * 0.0343f) / 2.0f;
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  float distCm = measureDistanceCm();

  if (distCm < 0) {
    Serial.println("Izvan dosega / nema odjeka");
  } else {
    Serial.print("Udaljenost: ");
    Serial.print(distCm, 1);
    Serial.println(" [cm]");
  }

  delay(200);
}

//Zadatak 5.2
const int TRIG_PIN = 2;   // D2
const int ECHO_PIN = 3;   // D3
const int BUZZER_PIN = 6; // D6

long measureDurationUs() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  return pulseIn(ECHO_PIN, HIGH, 30000);
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  long duration = measureDurationUs();
  if (duration == 0) {
    noTone(BUZZER_PIN);
    delay(150);
    return;
  }

  float distCm = (duration * 0.0343f) / 2.0f;
  Serial.print("Udaljenost: ");
  Serial.print(distCm, 1);
  Serial.println(" [cm]");

  if (distCm <= 100.0f) {
    int clampedDist = constrain((int)distCm, 5, 100);

    // Obrnuto proporcionalno: blize = visa frekvencija
    int freq = map(clampedDist, 5, 100, 2500, 400);
    // Kraci period ponavljanja kad je blize
    int pauseMs = map(clampedDist, 5, 100, 40, 500);

    tone(BUZZER_PIN, freq, 80);
    delay(80 + pauseMs);
  } else {
    noTone(BUZZER_PIN);
    delay(150);
  }
}