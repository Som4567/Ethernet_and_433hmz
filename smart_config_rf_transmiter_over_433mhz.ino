#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

//RH_ASK driver;
RH_ASK driver(2000,0);
// RH_ASK driver(2000, 2, 4, 5); // ESP8266 or ESP32: do not use pin 11



//Setup function connects nodemcu to wifi

void setup() {
  Serial.begin(115200);
  if (!driver.init())
         Serial.println("init failed");

  /* Set ESP8266 to WiFi Station mode */
  WiFi.mode(WIFI_STA);
  /* start SmartConfig */
  WiFi.beginSmartConfig();

  /* Wait for SmartConfig packet from mobile */
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("SmartConfig done.");

  /* Wait for WiFi to connect to AP */
  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  delay(1000);
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    char  buf_char[10]="\0";
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
  int i;
                  
  // Message with a good checksum received, dump it.
  driver.printBuffer("Got:", buf, buflen);

  Serial.println("buflen");
  Serial.println(buflen);
  Serial.println("RH_ASK_MAX_MESSAGE_LEN");
  Serial.println(RH_ASK_MAX_MESSAGE_LEN);
  //Converting the data to string 
  for (int i=0;i<buflen;i++)
  {
    buf_char[i]=(char)buf[i];
   // buf++;
  }

  buf_char[buflen-3]='.';
  
  Serial.println("buf_char is ");
  Serial.println(buf_char);
  //Sending the data to the server
  HTTPClient http;
    String str1="{\"product_id\":\"100\",\"level\":\"";
    String data2=(String)buf_char;
    String name2="\"}";

    String name3 =str1+data2+name2;
       
    String post_var=name3;
    Serial.print("[HTTP] begin...\n");
    http.begin("54.70.29.64", 9000, "/postLevel"); //HTTP
    http.addHeader("Content-Type","application/json");
    Serial.print("[HTTP] Post...\n");
    int httpCode= http.POST(post_var);
    if(httpCode) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            // file found at server
            if(httpCode == 200) {
                String payload = http.getString();
                Serial.println(payload);
             }
     }
     else {
            Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
     }



  
   }
    
  
}

