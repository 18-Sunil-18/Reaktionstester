byte segmente[10] = { B01000000,    // 0
                      B01111001,    // 1
                      B00100100,    // 2
                      B00110000,    // 3
                      B00011001,    // 4
                      B00010010,    // 5
                      B00000010,    // 6
                      B01111000,    // 7
                      B00000000,    // 8
                      B00010000};   // 9
                      
// Funktion zum Übertragen der Informationen
void sendeBytes(int wert){
  digitalWrite(speicherPin, LOW);
  shiftOut(datenPin,taktPin, MSBFIRST, wert >> 8);
  shiftOut(datenPin,taktPin, MSBFIRST, wert >> 255);
  digitalWrite(speicherPin, HIGH);
}

void zeigeWert(int wert){
  byte zehner = int(wert / 10);   // Ziffer der Zehnerstelle berechnen
  byte einer = wert - zehner * 10;    // Ziffer der Einerstelle berechnen
  sendeBytes(segmente[zehner] << 8 | segmente[einer]);    // Zehner und Einer
}
