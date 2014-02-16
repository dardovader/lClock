void funcionAlarma() {
  mostrarAlarma();
  BTN_FUN.read();
  if (BTN_FUN.wasPressed()) {
    estadoActual = M_AJUSTES;
  }
  switch (objAlrm) {
    case 0:
      BTN_SEL.read();
      if (BTN_SEL.wasPressed()) {
        objAlrm = 1;
      }
      BTN_ACC.read();
      if (BTN_ACC.wasPressed()) {
        if (hha < 23) {
          hha = hha++;
        }
        else {
          hha = 0;
        }
      }
      break;
    case 1:
      BTN_SEL.read();
      if (BTN_SEL.wasPressed()) {
        objAlrm = 2;
      }
      BTN_ACC.read();
      if (BTN_ACC.wasPressed()) {
        if (mma < 59) {
          mma = mma++;
        }
        else {
          mma = 0;
        }
      }
      break;
    case 2:
      BTN_SEL.read();
      if (BTN_SEL.wasPressed()) {
        objAlrm = 0;
      }
      BTN_ACC.read();
      if (BTN_ACC.wasPressed()) {
        if (alarmaON) {
          alarmaON=false;
          }
          else {
            alarmaON=true;
            }
      }
      break;
  }
}

void mostrarAlarma() {
  pantalla.setCursor(0, 0);
  pantalla.print("Alarma          ");
  pantalla.setCursor(0, 1);
  dosDigitosLCD(hha);
  pantalla.print(":");
  dosDigitosLCD(mma);
  if (alarmaON) {
    pantalla.print(" ON       ");
  }
  else {
    pantalla.print(" OFF      ");
  }
}
