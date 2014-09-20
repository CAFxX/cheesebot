#include "CAC_2.h"

// definisco a quali pin è connesso il display
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

// in un sottomodulo non si vedono direttamente variabili globali definite in altri sottomoduli
// per poterlo fare, bisogna dichiarare la variabile a cui si vuole accedere come extern 
// questo comunica al compilatore "fidati, so che questa variabile globale è definita in un altro sottomodulo"
extern stato_t stato;

void AggiornaDisplayStringa(int c, int r, char *str) {
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

void AggiornaDisplayStato(stato_t _stato) {
  switch (_stato) {
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
    
  AggiornaDisplayStringa(0, 0, "A-Temp");
  AggiornaDisplayStringa(0, 1, "B-Humi");
  AggiornaDisplayCarattere(10, 0, 0x7E); // freccia
  AggiornaDisplayCarattere(10, 1, 0x7E); // freccia

  AggiornaDisplaySensore(t, h);
  AggiornaDisplayTargetTemp(tt);
  AggiornaDisplayTargetHumi(th);
  AggiornaDisplayRelayTemp(0);
  AggiornaDisplayRelayHumi(0);
  AggiornaDisplayStato(stato);
}


