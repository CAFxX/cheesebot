#include "pins.h"

enum stato_t {   // stati dell'utente:
  STATO_0,       // nessuna modifica in corso
  MODIFICA_UMID, // utente sta modificando l'umidita'
  MODIFICA_TEMP  // utente sta modificando la temperatura
};

// VARIABILI DI STATO
// 4 int + 2 bool + 2 long + enum = 20 bytes
int t;                        // temperatura misurata dal sensore interno
int h;                        // umidita' misurata dal sensore interno
int t_ext;                    // temperatura misurata dal sensore esterno
int h_ext;                    // umidita' misurata dal sensore esterno
int tt;                       // temperatura target impostata dall'utente
int th;                       // umidita' target impostata dall'utente
bool relay_req = false;       // true se il relay deve essere attivo
bool fan_req = false;         // true se la ventola deve essere attiva
bool relay_on = false;        // true se il pin del relay e' HIGH
bool fan_on = false;          // true se il pin della ventola e' HIGH
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

void DecidiAzione() {
  relay_req = t > tt;
  fan_req = h > th;
}

void AggiornaOutput() {
  unsigned long curr_t = millis();
  
  // verifica se dobbiamo switchare (on->off o off->on) il frigo e se sono passati 
  // almeno RELAY_MIN_SWITCH_T millisecondi dall'ultimo switch
  if (relay_req != relay_on && curr_t - relay_switch_t >= RELAY_MIN_SWITCH_T) {
    relay_on = relay_req;
    relay_switch_t = curr_t;
    digitalWrite(PIN_RELAY, relay_on ? HIGH : LOW);
    AggiornaDisplayRelayTemp(relay_on ? 1 : 0);    
  }
  
  // verifica se dobbiamo switchare (on->off o off->on) la ventola e se sono passati 
  // almeno FAN_MIN_SWITCH_T millisecondi dall'ultimo switch
  bool fan_req = h > th;
  if (fan_req != fan_on && curr_t - fan_switch_t >= FAN_MIN_SWITCH_T) {
    fan_on = fan_req;
    fan_switch_t = curr_t;
    digitalWrite(PIN_FAN, fan_on ? HIGH : LOW);
    AggiornaDisplayRelayTemp(fan_on ? 1 : 0);    
  }
}

void loop() {
  GestisciTastiera(); // gestisci gli input dall'utente
  GestisciSensore(); // legge i dati dei sensori DHT
  DecidiAzione(); // in base alle letture dei sensori e all'input utente, decide cosa fare
  AggiornaOutput(); // aggiorna gli output, se necessario
}

void ResetSwitchTimes() {
  relay_switch_t = fan_switch_t = millis();
  relay_switch_t -= RELAY_MIN_SWITCH_T + 1;
  fan_switch_t -= FAN_MIN_SWITCH_T + 1;
}
