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
int i=1;
myStruct rxData;              // приёмная структура
byte buffer[sizeof(rxData)];  // приёмный буфер

void setup() {
  Serial.begin(115200);

  // ПИН ОБЯЗАТЕЛЬНО PULLUP!!!111
  pinMode(RX_PIN, INPUT_PULLUP);
}

void loop() {
   Serial.println("GBUS_read(RX_PIN, RX_ADDR, buffer, sizeof(buffer))="+GBUS_read(RX_PIN, RX_ADDR, buffer, sizeof(buffer)));
   delay(2000);
  if (GBUS_read(RX_PIN, RX_ADDR, buffer, sizeof(buffer))) {
    // если успешно приняли, распаковываем
    unpackDataBytes(buffer, rxData);
    delay(2000);
    // выводим проверяем
    Serial.println("rxData.id= "+String(rxData.id));
    Serial.println("rxData.isempty= "+String(rxData.isempty));
    Serial.println("rxData.h= "+String(rxData.h));
    Serial.println(i);
  }

  byte txaddr = GBUS_read_request(RX_PIN, RX_ADDR);
  if (txaddr) {
    Serial.print("Request from ");
    Serial.println(txaddr);
  }
  
   i=i+1;
}
