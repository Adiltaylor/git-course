// пакуем данные любого типа (например, структура) в буфер и отправляем
// принимаем и распаковываем в примере packData_mini_read

#include "GBUSmini.h"	// мини-библиотека с лёгкими функциями
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12); // RX, TX
unsigned char data[4] = {};
float distance;
int a01=0;
int a12=0;
int a23=0;
int a34=0;
int a=0;
int j=0;

//3-4 m
//3-2 m
//2-1 m
//высота - от 1300 (мм) до 3000 (мм)

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

int a01=0;
int a12=0;
int a23=0;
int a34=0;
int a=0;
int j=0;
  // ПИН ОБЯЗАТЕЛЬНО PULLUP!!!111
  pinMode(TX_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  mySerial.begin(9600);

  // заполняем структуру
  txData.id = 1;
  txData.isempty = 0;
  txData.h = 150;

  // пакуем структуру в буфер
  packDataBytes(buffer, txData);
}

void loop() {
  do {
    for (int i = 0; i < 4; i++)
    {
      data[i] = mySerial.read();
    }
  } while (mySerial.read() == 0xff);

  mySerial.flush();

  if (data[0] == 0xff)
  {
    int sum;
    sum = (data[0] + data[1] + data[2]) & 0x00FF;
    if (sum == data[3])
    {
      distance = (data[1] << 8) + data[2];
      if (distance > 280)
      {
        Serial.print("distance=");
        Serial.print(distance / 10);
        Serial.println("cm");
        if (distance>=0 && distance<100){
                a01=a01+1;
              }else if(distance>=1000 && distance<2000){
                  a12=a12+1;
              }
              else if(distance>=2000 && distance<3000){
                  a23=a23+1;
              }
              else if(distance>=3000 && distance<4000){
                  a34=a34+1;
              } 
              else { a=a+1;}
      } else
      {
        Serial.println("Below the lower limit");
      }
    } else Serial.println("ERROR");
  }
  delay(150);
  Serial.println("a12="+String(a12));
  // пин, адрес получателя, адрес отправителя, дата, размер
    if (j%100==0){
      txData.id = 1;
      txData.isempty = 0;
      txData.h = 10;
      
  GBUS_send(TX_PIN, RX_ADDR, TX_ADDR, buffer, sizeof(buffer));
  
       a01=0;
       a12=0;
       a23=0;
       a34=0;
       a=0;
       j=0;
    }
j=j+1;    
  
}
