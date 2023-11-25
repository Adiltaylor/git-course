// принимаем и распаковываем отправленные в примере packData_mini_send данные

#include "GBUSmini.h"  // мини-библиотека с лёгкими функциями

#define RX_PIN 4    // пин
#define RX_ADDR 3   // наш адрес

// структура для приёма
struct myStruct {
  byte id;
  byte isempty;
  float h;
};
myStruct rxData;              // приёмная структура
byte buffer[sizeof(rxData)];  // приёмный буфер

void setup() {
  Serial.begin(9600);

  // ПИН ОБЯЗАТЕЛЬНО PULLUP!!!111
  pinMode(RX_PIN, INPUT_PULLUP);
}

void loop() {
  if (GBUS_read(RX_PIN, RX_ADDR, buffer, sizeof(buffer))) {
    // если успешно приняли, распаковываем
    unpackDataBytes(buffer, rxData);
    
    // выводим проверяем
    Serial.println(rxData.id);
    Serial.println(rxData.isempty);
    Serial.println(rxData.h);
    Serial.println();
  }
}
