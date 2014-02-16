void funcionReloj() {
  unsigned long temp1 = millis();
  if (temp1 - preTemp1 > unSegundo) {
    preTemp1 = temp1;
    digitalClockDisplayDebug();
    Serial.print(luz);
    PintarReloj();
  }
  BTN_FUN.read();
  if (BTN_FUN.wasPressed()) {
    estadoActual = M_ALARMA;
  }
}


void PintarReloj() {
  // digital clock display of the time
  pantalla.setCursor(0, 0);
  dosDigitosLCD(hour());
  pantalla.print(":");
  dosDigitosLCD(minute());
  pantalla.print(":");
  dosDigitosLCD(second());
  pantalla.print("  ");
  pantalla.print(temperaturaC);
  pantalla.write(byte(0));
  pantalla.setCursor(0, 1);
  dosDigitosLCD(day());
  pantalla.print("/");
  dosDigitosLCD(month());
  pantalla.print("/");
  pantalla.print(year());
  pantalla.setCursor(15, 1);
  if (alarmaON) {
    pantalla.write(byte(2));
  }
  else {
    pantalla.write(byte(1));
  }
}


void digitalClockDisplayDebug() {
  // digital clock display of the time
  dosDigitos(hour());
  Serial.print(":");
  dosDigitos(minute());
  Serial.print(":");
  dosDigitos(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(year());
  Serial.println();
}

void dosDigitos(int n) {
  if (n < 10) {
    Serial.print("0");
  }
  Serial.print(n);

}


void dosDigitosLCD(int n) {
  if (n < 10) {
    pantalla.print("0");
  }
  pantalla.print(n);
}
