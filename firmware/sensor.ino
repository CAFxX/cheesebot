#include <DHT11.h>
#include "pins.h"

// definisco il tipo di sensore
#define DHTTYPE DHT11
DHT11 dht11(PIN_DHT);

void GestisciSensore() {
  // leggi i valori dal sensore
  float _h, _t;
  int res = dht11.read(_h, _t);
  int __h = (int)_h, __t = (int)_t;
  if (res == 0 && (h != __h || t != __t)) {
    h = __h;
    t = __t;
    AggiornaDisplaySensore(t, h);
  }
}
