#include <HardwareSerial.h>
HardwareSerial mySerial(1);
unsigned char data[4] = {};
float distance;
void setup()
{
  mySerial.begin(9600, SERIAL_8N1, 14, 12);
  Serial.begin(115200);
}

void loop()
{
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
      } else
      {
        Serial.println("Below the lower limit");
      }
    } else  {Serial.println(distance / 10); Serial.println("ERROR");}
  }
  delay(150);
}