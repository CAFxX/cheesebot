#include "pins.h"

enum stato_t {   // stati dell'utente:
  STATO_0,       // nessuna modifica in corso
  MODIFICA_UMID, // utente sta modificando l'umidita'
  MODIFICA_TEMP  // utente sta modificando la temperatura
};

// VARIABILI DI STATO
// 4 int + 2 bool + 2 long + enum = 20 bytes
int t;                        // temperatura misurata dal sensore 
int h;                        // umidita' misurata dal sensore
int tt;                       // temperatura target impostata dall'utente
int th;                       // umidita' target impostata dall'utente
bool relay_on = false;        // true se il relay e' attivo
bool fan_on = false;          // true se la ventola e' attiva
unsigned long relay_switch_t; // ultimo switch di stato del pin del relay
unsigned long fan_switch_t;   // ultimo switch di stato del pin della ventola
stato_t stato = STATO_0;      // stato dell'interfaccia utente

#define RELAY_MIN_SWITCH_T 20000
#define FAN_MIN_SWITCH_T 5000

void setup() {
  InizializzaDisplay();
  InizializzaSensore();
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);
  ResetSwitchTimes();
}

void loop() {
  GestisciTastiera(); // gestisci gli input dall'utente
  GestisciSensore(); // legge i dati dal sensore DHT
  
  unsigned long curr_t = millis();
  
  // verifica se dobbiamo switchare (on->off o off->on) il frigo e se sono passati 
  // almeno RELAY_MIN_SWITCH_T millisecondi dall'ultimo switch
  bool relay_required = t > tt;
  if (relay_required != relay_on && curr_t - relay_switch_t > RELAY_MIN_SWITCH_T) {
    relay_on = relay_required;
    relay_switch_t = curr_t;
    digitalWrite(PIN_RELAY, relay_on ? HIGH : LOW);
    AggiornaDisplayRelayTemp(relay_on ? 1 : 0);    
  }
  
  // verifica se dobbiamo switchare (on->off o off->on) la ventola e se sono passati 
  // almeno FAN_MIN_SWITCH_T millisecondi dall'ultimo switch
  bool fan_required = h > th;
  if (fan_required != fan_on && curr_t - fan_switch_t > FAN_MIN_SWITCH_T) {
    fan_on = fan_required;
    fan_switch_t = curr_t;
    digitalWrite(PIN_FAN, fan_on ? HIGH : LOW);
    AggiornaDisplayRelayHumi(fan_on ? 1 : 0);    
  }
}

void ResetSwitchTimes() {
  relay_switch_t = fan_switch_t = millis();
}
