#include "pins.h"

// stati dell'utente
enum stato_t { 
  STATO_0,       // nessuna modifica in corso
  MODIFICA_UMID, // utente sta modificando l'umidita'
  MODIFICA_TEMP  // utente sta modificando la temperatura
};

// VARIABILI DI STATO
int t;                   // temperatura misurata dal sensore 
int h;                   // umidita' misurata dal sensore
int tt;                  // temperatura target impostata dall'utente
int th;                  // umidita' target impostata dall'utente
bool relay_on = false;   // true se il relay e' attivo
bool fan_on = false;     // true se la ventola e' attiva
long relay_switch_t = 0; // ultimo switch di stato del pin del relay
long fan_switch_t = 0;   // ultimo switch di stato del pin della ventola
stato_t stato = STATO_0; // stato dell'interfaccia utente

void setup() {
  Serial.begin(9600);
  InizializzaDisplay();
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);
}

void loop() {
  GestisciTastiera(); // gestisci gli input dall'utente
  GestisciSensore(); // legge i dati dal sensore DHT
  
  long curr_t = millis();
  
  bool relay_required = t > tt;
  if (relay_required != relay_on && curr_t - relay_switch_t > RELAY_MIN_SWITCH_T) {
    relay_on = relay_required;
    relay_switch_t = curr_t;
    digitalWrite(PIN_RELAY, relay_on ? HIGH : LOW);
    AggiornaDisplayRelayTemp(relay_on ? 1 : 0);    
  }
  
  bool fan_required = h > th;
  if (fan_required != fan_on && curr_t - fan_switch_t > FAN_MIN_SWITCH_T) {
    fan_on = fan_required;
    fan_switch_t = curr_t;
    digitalWrite(PIN_FAN, fan_on ? HIGH : LOW);
    AggiornaDisplayRelayTemp(fan_on ? 1 : 0);    
  }
  
}
