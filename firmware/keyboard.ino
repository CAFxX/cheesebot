#include <Keypad.h>
#include "pins.h"

#define KEY_ROWS 4
#define KEY_COLS 4 

// TODO: move keys, rowPins and colPins in FLASH

// Define the Keymap
const char keys[KEY_ROWS][KEY_COLS] = {
  {  '1','2','3','A'  },
  {  '4','5','6','B'  },
  {  '7','8','9','C'  },
  {  '*','0','#','D'  }
};

// pin della tastiera
byte rowPins[KEY_ROWS] = { PIN_KEY_ROW_0, PIN_KEY_ROW_1, PIN_KEY_ROW_2, PIN_KEY_ROW_3 };
byte colPins[KEY_COLS] = { PIN_KEY_COL_0, PIN_KEY_COL_1, PIN_KEY_COL_2, PIN_KEY_COL_3 }; 

// Create the Keypad
Keypad k( makeKeymap(keys), rowPins, colPins, KEY_ROWS, KEY_COLS );

// si imposta una struttura a stati per identificare che tipo di tasto è premuto (num., lettera, etc) per programmarne il comportamento. 
// Tutta la logica di tastiera, variabili comprese dovrebbe essere gestita qui. 

void GestisciTastiera()
{
  // variabile di stato (non globale) per l'input da tastiera di valori numerici
  static int num = 0;
  
  // legge 
  char key1 = k.getKey(); // leggi
  switch (key1)
  {
  default: // il default rende piu chiaro il codice.
    case NO_KEY:
      break;

  case 'A':
    switch (stato) {
      case MODIFICA_TEMP: AggiornaDisplayTargetTemp(tt); break;
      case MODIFICA_UMID: AggiornaDisplayTargetHumi(th); break;
    }
    stato = MODIFICA_TEMP;
    num = tt;
    AggiornaDisplayStato();
    break;
    
  case 'B':
    switch (stato) {
      case MODIFICA_TEMP: AggiornaDisplayTargetTemp(tt); break;
      case MODIFICA_UMID: AggiornaDisplayTargetHumi(th); break;
    }
    stato = MODIFICA_UMID;
    num = th;
    AggiornaDisplayStato();
    break;
    
  case '0': 
  case '1': 
  case '2': 
  case '3': 
  case '4':
  case '5': 
  case '6': 
  case '7': 
  case '8': 
  case '9':
    // interpreta la cifra premuta e aggiorna il display a due cifre
    num = ( num * 10 + (key1 - '0') ) % 100;
    
    switch (stato) {
      case MODIFICA_TEMP: AggiornaDisplayTargetTemp(num); break;
      case MODIFICA_UMID: AggiornaDisplayTargetHumi(num); break;
    }
    break;

  case '#':
    switch (stato) {
      case STATO_0:       return;
      case MODIFICA_TEMP: tt = num; break;
      case MODIFICA_UMID: th = num; break;
    }
    stato = STATO_0;
    AggiornaDisplayStato();
    ResetSwitchTimes(); 
    break;
    
  }
}
