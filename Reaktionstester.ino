#define TASTER 4    // Taster-Pin
#define TASTER_1 3    // Taster-Pin zum Zurücksetzen
#define LEDROT 7   // LED-Pin Rot
#define LEDGELB 6    // LED-Pin Gelb
#define LEDGRUEN 5   // LED-Pin Grün
#define LEVEL 5   // Schwierigkeits-Level

int taktPin = 8;    // SH_CP
int speicherPin = 9;    // ST_CP
int datenPin = 10;    // DS
byte phase = 0;   // 1 = Rot, 2 = Gelb, 3 = Grün
long startPunkt = 0;    // Wenn Taster gedrückt -> Startpunkt
byte anzeigeWert, stopZeit;
boolean taster = false, gestoppt = false;

void setup(){
  pinMode(taktPin, OUTPUT);
  pinMode(speicherPin, OUTPUT);
  pinMode(datenPin, OUTPUT);
  pinMode(TASTER, OUTPUT);
  pinMode(LEDROT, OUTPUT);
  pinMode(LEDGELB, OUTPUT);
  pinMode(LEDGRUEN, OUTPUT);
}

void loop(){
  taster = digitalRead(TASTER);
  if(phase < 3) zeigeWert(0);   // Zeige am Anfang 00 in der Anzeige
  // Steuerung der Ampelphasen
  if((taster) && (startPunkt == 0)){
    phase = 1;    // Beginne mit Rot
    startPunkt = millis();
  }
  if((phase == 1) && (millis() - startPunkt > 2000))
    digitalWrite(LEDROT, HIGH);
  if((phase == 1) && (millis() - startPunkt > 4000)){
    digitalWrite(LEDGELB, HIGH);
    phase = 2;    // Gelb
  }
  if((phase == 2) && (millis() - startPunkt > 6000)){
    digitalWrite(LEDROT, LOW);
    digitalWrite(LEDGELB, LOW);
    digitalWrite(LEDGRUEN, HIGH);
    phase = 3;    // Grün
  }
  // Zählehoch, wenn LED Grün und noch nicht gestoppt wurde
  if((phase == 3) && (!gestoppt))
    zeigeWert(anzeigeWert++);
  delay(LEVEL);   // Schwierigkeits-Level
  // Leuchtet LED Grün und der Taster wurde gedrückt
  if((taster) && (phase == 3)){
    gestoppt = true;    // Flag für gestoppt auf "wahr" setzen
    stopZeit = anzeigeWert;   // Stopzeit sichern
     // Zurücksetzen auf den Anfang neustart();
  }
  neustart();
  // Wenn gestoppt, dann Stopzeit anzeigen
  if(gestoppt)
    zeigeWert(stopZeit);
  // Wenn in Gelbphase gedrückt -> zu früh
  if((taster) && (phase == 2))
    blinken();
  // Wenn überhaupt nicht reagiert wird -> blinken
  if(anzeigeWert == 99)
    blinken();
}
