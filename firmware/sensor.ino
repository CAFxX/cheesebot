#include <DHT.h>
#include "pins.h"

DHT dht_int;
DHT dht_ext;

void InizializzaSensore() {
  dht_int.setup(PIN_DHT_INT);
  dht_ext.setup(PIN_DHT_EXT);
}

void GestisciSensore() {
  // leggi i valori dal sensore interno
  if (dht_int.getStatus() == DHT::ERROR_NONE) {
    int hn = (int)dht_int.getHumidity(), tn = (int)dht_int.getTemperature();
    if (hn != h || tn != t) {
      AggiornaDisplaySensore(t = tn, h = hn);
    }
  }
  // leggi i valori dal sensore esterno
  if (dht_ext.getStatus() == DHT::ERROR_NONE) {
    int hn = (int)dht_ext.getHumidity(), tn = (int)dht_ext.getTemperature();
    if (hn != h_ext || tn != t_ext) {
      t_ext = tn; 
      h_ext = hn;
    }
  }
}
