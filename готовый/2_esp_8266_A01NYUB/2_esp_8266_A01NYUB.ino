
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t broadcastAddress1[] = {0x98, 0xCD, 0xAC, 0x7A, 0x49, 0x58};

typedef struct test_struct {
    int x;
    int y;
} test_struct;

// Create a struct_message called test to store variables to be sent
test_struct test;

SoftwareSerial mySerial(14, 12); // RX, TX
unsigned char data[4] = {};
float distance;
/*test_struct test;
typedef struct test_struct {
    int x;
    int y;
} test_struct */



unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  // send readings timer

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  char macStr[18];
  Serial.print("Packet to:");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

void setup()
{
  Serial.begin(57600);
  mySerial.begin(9600);

WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop()
{
  for(int j =1; j<=100;j++){
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
    } else Serial.println("ERROR");
  }


    if (j%100==0){
       
    if ((millis() - lastTime) > timerDelay) {
        // Set values to send
        test.x = 2;
        test.y =distance;
    // Send message via ESP-NOW
      esp_now_send(0, (uint8_t *)  &test, sizeof(test));

    lastTime = millis();
  }
          }
  delay(150);
 } 
}