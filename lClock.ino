/*********************************************************
*
*  lClock: Reloj LED con Arduino
*
*  Proyecto por Samuel Villafranca Gómez
*
*  Este código usa código de terceros :-)
**********************************************************/

//Librerías
#include <Button.h>
#include <LiquidCrystal.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <TimeAlarms.h>
#include <EEPROM.h>

//Datos relacionados con la máquina de estados
enum estados {M_RELOJ, M_ALARMA, M_AJUSTES};

estados estadoActual = M_RELOJ;


//Nombramos los pines que vamso a utilizar
#define P_BTN_FUN  8
#define P_BTN_SEL  7
#define P_BTN_ACC  6
#define P_TMP_SENS 0
#define P_LUZ_SENS 1

//Declaramos los botones
Button BTN_FUN(P_BTN_FUN, true, true, 20);
Button BTN_SEL(P_BTN_SEL, true, true, 20);
Button BTN_ACC(P_BTN_ACC, true, true, 20);

//Temporizadores
const long unSegundo = 1000;
long preTemp1 = 0;
long preTemp2 = 0;

//Definimos la pantalla
LiquidCrystal pantalla(12, 11, 5, 4, 3, 2);
byte tCelsius[8] = {
  B11000,
  B11000,
  B00110,
  B01001,
  B01000,
  B01000,
  B01001,
  B00110,
};

byte campana[8] = {
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B11111,
  B00100,
  B00000,
};

byte campanaN[8] = {
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B11111,
  B00100,
  B00000,
};

//Variable para datos de sensores
float temperaturaC;
int luz;

//Variables para la alarma
int hha = 06;
int mma = 30;
bool alarmaON = false;
int objAlrm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pantalla.begin(16, 2);
  pantalla.createChar(0, tCelsius);
  pantalla.createChar(1,campana);
  pantalla.createChar(2,campanaN);
}

void loop() {
  int lecturaTMP = analogRead(P_TMP_SENS);
  float voltage = lecturaTMP * 5.0;
  voltage /= 1024.0;
  temperaturaC = (voltage - 0.5) * 100;
  luz = analogRead(P_LUZ_SENS);

  // put your main code here, to run repeatedly:
  switch (estadoActual) {
    case M_RELOJ: funcionReloj(); break;
    case M_ALARMA: funcionAlarma(); break;
    case M_AJUSTES: funcionAjustes(); break;
  }
}




void funcionAjustes() {
  Serial.println("Entrando en modo ajustes");
  BTN_FUN.read();
  if (BTN_FUN.wasPressed()) {
    estadoActual = M_RELOJ;
  }
}
