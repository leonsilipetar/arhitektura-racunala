//Zadatak 6.1
void setup() {
  Serial.begin(9600);

  // Bez F() - zauzima SRAM za tekstualni literal:
  // Serial.println("Ovo je primjer dugackog stringa. Dodajemo jos teksta za testiranje zauzeca memorije.");

  // Sa F() - ostaje u Flash memoriji:
  Serial.println(F("Ovo je primjer dugackog stringa."));
  Serial.println(F("Dodatni tekst spremljen u Flash memoriju kako bi se ustedio SRAM."));
}

void loop() {
}

//Zadatak 6.2
#include <EEPROM.h>

const int ADR_BROJAC = 0;
byte brojac = 0;

void setup() {
  Serial.begin(9600);
  delay(200);

  brojac = EEPROM.read(ADR_BROJAC);
  Serial.print("Ucitana vrijednost iz EEPROM-a: ");
  Serial.println(brojac);
}

void loop() {
  delay(1000);

  brojac = (brojac + 1) % 256;
  EEPROM.write(ADR_BROJAC, brojac);

  Serial.print("Novi brojac (spremljen u EEPROM): ");
  Serial.println(brojac);
}