// пакуем данные любого типа (например, структура) в буфер и отправляем
// принимаем и распаковываем в примере packData_mini_read

#include "GBUSmini.h"	// мини-библиотека с лёгкими функциями

#define TX_PIN 4    // пин
#define RX_ADDR 3   // адрес приёмника
#define TX_ADDR 5   // наш адрес

// структура для отправки
struct myStruct {
  byte id;
  byte isempty;
  int h;
};
myStruct txData;              // отправная структура
byte buffer[sizeof(txData)];  // отправной буфер

void setup() {
  // ПИН ОБЯЗАТЕЛЬНО PULLUP!!!111
  pinMode(TX_PIN, INPUT_PULLUP);

  // заполняем структуру
  txData.id = 1;
  txData.isempty = 0;
  txData.h = 150;

  // пакуем структуру в буфер
  packDataBytes(buffer, txData);
}

void loop() {
  // пин, адрес получателя, адрес отправителя, дата, размер
  GBUS_send(TX_PIN, RX_ADDR, TX_ADDR, buffer, sizeof(buffer));
  delay(4000);
}
