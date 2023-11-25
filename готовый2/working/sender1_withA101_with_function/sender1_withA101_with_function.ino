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
  float h;
};
myStruct txData;              // отправная структура
byte buffer[sizeof(txData)];  // отправной буфер

float dis(){
  float distancer=0;
   for (int a = 0; a < 2000; a++){
   do {
    for (int i = 0; i < 4; i++)
    {
      data[i] = mySerial.read();
    //Serial.println("data["+ String(i) + "]=" +String(data[i]));
    }
  } while (mySerial.read() == 0xff);

  mySerial.flush();

  if (data[0] == 0xff)
  {
    int sum;
    sum = (data[0] + data[1] + data[2]) & 0x00FF;
    if (sum == data[3])
    {
      distancer = (data[1] << 8) + data[2];
      if (distancer > 280)
      {
        //Serial.print("distance=");
        //Serial.print(distance / 10);
        //Serial.println("cm");
        return distancer;
      } /*else
      {
        Serial.println("Below the lower limit");
      }*/
    } /*else {Serial.println("ERROR"); }*/
  } 

  delay(120);
   }
}
void setup() {

  // ПИН ОБЯЗАТЕЛЬНО PULLUP!!!111
  pinMode(TX_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  mySerial.begin(9600);

  // заполняем структуру
 // txData.id = 1;
 // txData.isempty = 0;
 // txData.h = 150;
   
     
  // пакуем структуру в буфер
  //packDataBytes(buffer, txData);
}

void loop() {
  distance=dis();
  delay(1000);
  
      txData.id = 1;
      txData.isempty = 0;
      txData.h =distance;
      delay(500);
      packDataBytes(buffer, txData); 
      delay(500);
      Serial.println("dis()="+String(dis()));
       Serial.println("txData.id="+String(txData.id)); 
  Serial.println("txData.isempty="+String(txData.isempty)); 
  Serial.println("txData.h="+String(txData.h));
  
   mySerial.end();
   delay(500);
//Serial.println("dis()="+String(dis()));
  
      
      
//Serial.println("dis()="+String(dis()));      
//delay(1000);
/*
  Serial.println("txData.id="+String(txData.id)); 
  Serial.println("txData.isempty="+String(txData.isempty)); 
  Serial.println("txData.h="+String(txData.h)); 
*/  
    
    GBUS_send(TX_PIN, RX_ADDR, TX_ADDR, buffer, sizeof(buffer));
    delay(2000);
     mySerial.begin(9600);
       
}
