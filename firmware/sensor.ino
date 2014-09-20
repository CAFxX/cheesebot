#include <DHT.h>
#include "pins.h"

DHT dht;

void InizializzaSensore() {
  dht.setup(PIN_DHT);
}

void GestisciSensore() {
  // leggi i valori dal sensore
  if (dht.getStatus() == DHT::ERROR_NONE) {
    int hn = (int)dht.getHumidity(), tn = (int)dht.getTemperature();
    if (hn != h || tn != t) {
      AggiornaDisplaySensore(t = tn, h = hn);
    }
  }
}
