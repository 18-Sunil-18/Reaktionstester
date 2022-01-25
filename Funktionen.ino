// Wird aufgerufen, wenn der Taster vor der Grün-Phase gedrückt wird
void blinken(){
  digitalWrite(LEDROT, HIGH);
  digitalWrite(LEDGELB, LOW);
  digitalWrite(LEDGRUEN, LOW);

  for(int i = 0; i < 30; i++){
    digitalWrite(LEDROT, (i%2 == 0)?HIGH:LOW);
    delay(50);
    zeigeWert(99);
  }
  reset();
}

// Auf Anfangswerte zurücksetzen
void reset(){
  phase = 0, startPunkt = 0, stopZeit = 0;
  anzeigeWert = 0;
  taster = false, gestoppt = false;
  digitalWrite(LEDROT, LOW);
  digitalWrite(LEDGELB, LOW);
  digitalWrite(LEDGRUEN, LOW);
}

// Zurücksetzen auf den Anfang
void neustart(){
  if(digitalRead(TASTER_1) == HIGH){
    reset();
  }
}
