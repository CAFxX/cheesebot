#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#include "pins.h"

extern stato_t stato;

// definisco a quali pin è connesso il display
LiquidCrystal lcd(PIN_LCD_0, PIN_LCD_1, PIN_LCD_2, PIN_LCD_3, PIN_LCD_4, PIN_LCD_5);

void AggiornaDisplayPSTR(int c, int r, const char* PROGMEM progmem_str) {
  char str[16+1];
  strlcpy_P(str, progmem_str, sizeof(str));
  AggiornaDisplayStringa(c, r, str);
}

void AggiornaDisplayStringa(int c, int r, const char *str) {
  lcd.setCursor(c, r);
  lcd.print(str);
}

void AggiornaDisplayCarattere(int c, int r, char car) {
  lcd.setCursor(c, r);
  lcd.print(car);
}

void AggiornaDisplayNumero(int c, int r, int val) {
  if (val >= 0) {
    char str[3];
    snprintf(str, 3, "%2d", val);
    lcd.setCursor(c, r);
    lcd.print(str);
  }
}

void AggiornaDisplaySensore(int _t, int _h) {
  AggiornaDisplayNumero(7, 0, _t);
  AggiornaDisplayNumero(7, 1, _h);
}

void AggiornaDisplayTargetTemp(int _tt) {
  AggiornaDisplayNumero(12, 0, _tt);
}

void AggiornaDisplayTargetHumi(int _th) {
  AggiornaDisplayNumero(12, 1, _th);
}

void AggiornaDisplayRelayTemp(int relayt) {
  if (relayt >= 0) {
    AggiornaDisplayCarattere(15, 0, relayt == 0 ? ' ' : '*');
  }  
}

void AggiornaDisplayRelayHumi(int relayh) {
  if (relayh >= 0) {
    AggiornaDisplayCarattere(15, 1, relayh == 0 ? ' ' : '*');
  }  
}

void AggiornaDisplayStato() {
  switch (stato) {
    case STATO_0:
      AggiornaDisplayCarattere(11, 0, ' ');
      AggiornaDisplayCarattere(14, 0, ' ');
      AggiornaDisplayCarattere(11, 1, ' ');
      AggiornaDisplayCarattere(14, 1, ' ');
      break;
    case MODIFICA_TEMP:
      AggiornaDisplayCarattere(11, 0, '[');
      AggiornaDisplayCarattere(14, 0, ']');
      AggiornaDisplayCarattere(11, 1, ' ');
      AggiornaDisplayCarattere(14, 1, ' ');
      break;
    case MODIFICA_UMID:
      AggiornaDisplayCarattere(11, 0, ' ');
      AggiornaDisplayCarattere(14, 0, ' ');
      AggiornaDisplayCarattere(11, 1, '[');
      AggiornaDisplayCarattere(14, 1, ']');
      break;
  }
}

void InizializzaDisplay() {
  lcd.begin(16, 2);
    
  AggiornaDisplayPSTR(0, 0, PSTR("A-Temp"));
  AggiornaDisplayPSTR(0, 1, PSTR("B-Humi"));
  AggiornaDisplayCarattere(10, 0, 0x7E); // freccia
  AggiornaDisplayCarattere(10, 1, 0x7E); // freccia

  AggiornaDisplaySensore(t, h);
  AggiornaDisplayTargetTemp(tt);
  AggiornaDisplayTargetHumi(th);
  AggiornaDisplayRelayTemp(0);
  AggiornaDisplayRelayHumi(0);
  AggiornaDisplayStato();
}


