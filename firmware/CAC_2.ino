#include <Keypad.h>
#include <DHT11.h>
#include <LiquidCrystal.h>
#include "CAC_2.h"

// definisco il pin del sensore temperatura cavo 3
#define DHTPIN A1
// definisco il tipo di sensore
#define DHTTYPE DHT11
DHT11 dht11(DHTPIN);
//(DHTPIN, DHTTYPE);

// definisco che il pin 13 è quello a cui è connesso relay (frigorifero)
#define PIN_RELAY 13
// definisco che il pin 12 è quello a cui è connessa la ventola
#define PIN_FAN 12

int t, h;  //variabili misurate
int tt, th;  //variabili target

void setup() {
  Serial.begin(9600);
  InizializzaDisplay();
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);
}

void loop() {
  // gestisci gli input dall'utente
  GestisciTastiera();
  
  // leggi i valori dal sensore
  float _h, _t;
  int res = dht11.read(_h, _t);
  int __h = (int)_h, __t = (int)_t;
  if (res == 0 && (h != __h || t != __t)) {
    h = __h;
    t = __t;
    AggiornaDisplaySensore(t, h);
  }
  
  // attiva/disattiva il relay della presa (frigorifero)
  if (t < tt) {
    // spengo il frigo
    digitalWrite(PIN_RELAY, LOW);
    AggiornaDisplayRelayTemp(0);
  } else {
    // accendo il frigo
    digitalWrite(PIN_RELAY, HIGH);
    AggiornaDisplayRelayTemp(1);
  }

  // attiva/disattiva la ventola 
  if (h < th) {
    // spengo la ventola
    digitalWrite(PIN_FAN, LOW);
    AggiornaDisplayRelayHumi(0);
  } else {
    // accendo la ventola
    digitalWrite(PIN_FAN, HIGH);
    AggiornaDisplayRelayHumi(1);
  }

}    


