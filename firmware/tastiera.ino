#include "CAC_2.h"

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {  '1','2','3','A'  },
  {  '4','5','6','B'  },
  {  '7','8','9','C'  },
  {  '*','0','#','D'  }
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { A5, A4, A3, A2 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3, 2 }; 
// Create the Keypad
Keypad k( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// questo è da considerare una variabile globale poiche e qui in cima
int num = 0;
stato_t stato = STATO_0;

// si imposta una struttura a stati per identificare che tipo di tasto è premuto (num., lettera, etc) per programmarne il comportamento. 
// Tutta la logica di tastierra, variabili comprese dovrebbe essere gestita qui. 

void GestisciTastiera()
{
  // legge 
  char key1 = k.getKey();
  switch (key1)
  {
  case 'A':
    stato = MODIFICA_TEMP;
    num = tt;
    AggiornaDisplayTargetTemp(tt);
    AggiornaDisplayTargetHumi(th);
    AggiornaDisplayStato(stato);
    break;
    
  case 'B':
    stato = MODIFICA_UMID;
    num = th;
    AggiornaDisplayTargetTemp(tt);
    AggiornaDisplayTargetHumi(th);
    AggiornaDisplayStato(stato);
    break;
    
  default: // il default rende piu chiaro il codice.
  case NO_KEY:
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
    if (stato == STATO_0)
      break;
    
    num = num * 10 + (key1 - '0');
    //questo serve a costruire il numero a due cifre

    num = num % 100;
      // trova il resto dalla divisione per 100
      
    // passa -1 nei campi da non aggiornare
    if (stato == MODIFICA_TEMP)
      AggiornaDisplayTargetTemp(num);
    else if (stato == MODIFICA_UMID)
      AggiornaDisplayTargetHumi(num);
 
    break;

  case '#':
    if (stato == MODIFICA_TEMP)
      tt = num;
    else if (stato == MODIFICA_UMID)
      th = num;
    stato = STATO_0;
    AggiornaDisplayStato(stato);
  }
}

