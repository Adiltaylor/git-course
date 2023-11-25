// Node 1 code 
#include<SoftwareSerial.h>

#define RS_RO 10
#define RS_DI 11
#define RS_DE_RE 12

SoftwareSerial RS_SN(RS_RO, RS_DI); // RX_TX

void setup(){
    Serial.begin(9600);
    RS_SN.begin(9600);
    pinMode(RS_DE_RE, OUTPUT);
    digitalWrite(RS_DE_RE, LOW);

    Serial.println("Node 1 is ready. .....");
}
void loop(){
if (Serial.available()){
    digitalWrite(RS_DE_RE,HIGH);
    RS_SN.write(Serial.read());
    delay(10);
    digitalWrite(RS_DE_RE,LOW);
    }
    if (RS_SN.available()){
        Serial.write(RS_SN.read());
    }
}
