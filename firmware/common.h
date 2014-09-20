// questo header contiene le dichiarazioni comuni

#ifndef COMMON
#define COMMON

#define PIN_DHT       A1  // pin dati del sensore DHT
#define PIN_RELAY     13  // output pin verso il relay del frigorifero
#define PIN_FAN       12  // output pin verso il relay della ventola
#define PIN_KEY_ROW_0 A5  // pin della tastiera (keyboard.ino)
#define PIN_KEY_ROW_1 A4  //
#define PIN_KEY_ROW_2 A3  //
#define PIN_KEY_ROW_3 A2  //
#define PIN_KEY_COL_0 5   //
#define PIN_KEY_COL_1 4   //
#define PIN_KEY_COL_2 3   //
#define PIN_KEY_COL_3 2   //

// enum: definisce tipo variabile che puo avere dei valori solo presenti nei parametri enumerati in parentesi.
enum stato_t { STATO_0, MODIFICA_UMID, MODIFICA_TEMP };

#endif // COMMON
