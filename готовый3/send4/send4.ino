// отправляем структуру через SoftwareSerial
// отправляет esp8266 (этот скетч), принимает Ардуина
// Провод подключен к D2 ноды и D10 Ардуины

#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 4); // RX, TX
// ВНИМАНИЕ! Нужно указывать номера GPIO, а не D-пины
// на Node получается RX-D1, TX-D2

#include "GBUS.h"
int plata=7;
int plata_reciver=3;
// адрес 5, буфер 20 байт
GBUS bus(&mySerial, plata, 20); //1 плата

// структура для отправки
// БУДЬ ВНИМАТЕЛЕН, ЛЮБИТЕЛЬ ESP8266!!
// Тут данные кодируются хрен пойми как, компилятор "не смог"
// сначала располагай тяжёлые типы данных (float, int, long)
// РАСПОЛАГАЙ БАЙТЫ В КОНЦЕ СТРУКТУРЫ!
// int тут занимает 4 байта, так что на Arduino его нужно принимать как long!!!
// структура структур должна быть одинаковая
struct myStruct {
  float val_f;
  float val_f2;
  //int val_i;
  //long val_l;
  byte val_b;
};

void setup() {
  // родной сериал открываю для наблюдения за процессом
  Serial.begin(9600);
  // этот сериал будет принимать данные
  // мы указали его как обработчик
  mySerial.begin(9600);
  //delay(6000); //4 плата
}

void loop() {
  Serial.println("transmitting");
  myStruct data;
  // забиваем данные
  data.val_f = 11.11;
  data.val_f2 = 11.78;
  //data.val_i = 12;
  //data.val_l = 13;
  data.val_b = 4;
  // отправляем на адрес 3
   bus.sendData(plata_reciver, data);
  delay(2000);

  // tick() тут не нужен! Он занимается только приёмом данных
  // отправка делается так, как реализовано в используемой либе интерфейса
}
