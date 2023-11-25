// Base station code 
#include<SoftwareSerial.h>

#define RS_RO 10
#define RS_DI 11
#define RS_DE_RE 12

SoftwareSerial RS_BS(RS_RO, RS_DI); // RX_TX

void setup(){
    Serial.begin(9600);
    RS_BS.begin(9600);
    pinMode(RS_DE_RE, OUTPUT);
    digitalWrite(RS_DE_RE, HIGH);
    Serial.println("Base-Station is ready. .....");
}
void loop(){
if (Serial.available()){
    digitalWrite(RS_DE_RE,OUTPUT);
    RS_BS.write(Serial.read());
    delay(10);
    digitalWrite(RS_DE_RE,LOW);
    }
    if (RS_BS.available()){
        Serial.write(RS_BS.read());
    }
}
