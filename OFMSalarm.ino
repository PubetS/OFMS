
// LINE_TOKEN

void Line_Notify(String message);
void Line_Notify(String bat);


#include <ESP8266WiFi.h>
#include <WiFiClientSecureAxTLS.h> 

// Config connect WiFi
#define WIFI_SSID "OPPO Reno5 5G"
#define WIFI_PASSWORD "r6vyxaih"

// Line config
#define LINE_TOKEN "wHazKTZFHUc0coshmiV1ZBK8yzxwA4Y84bpBi6VSolr"

#define SW D2  // ต่อเข้า pin 49 ของ arduino mega
#define SW2 D5 // ต่อเข้า pin 47 ของ arduino mega 

String message = "SafWit ทดสอบ"; 
String bat = "Power outage";
String sys = "Optical link connected";
String hello = "hello";

boolean P= true;
void setup() {
  pinMode(SW, INPUT);
  pinMode(SW2, INPUT);
  

  Serial.begin(9600);

  // connect to wifi.
  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Line_Notify(hello);
}

void loop() {

  // เว็บที่ไว้แปลงภาษาไทย https://meyerweb.com/eric/tools/dencoder/
  message = "Optical link failed !! The system will alert again within 45 minutes if the fiber cable still cannot be used"; 
  bat = "Power Outage";
  sys = "Fiber cable is connected.";


if(digitalRead(SW) == LOW && digitalRead(SW2) == LOW){
  while(P==true){
    delay(500);
    Serial.println("Power outage");
    Line_Notify(bat);
   P=false;
  }
}



 if (digitalRead(SW) == HIGH && digitalRead(SW2) == LOW) {
        delay(500);
        Serial.println("Optical link connected");
      

        if(digitalRead(SW) == LOW && digitalRead(SW2) == LOW){                                                ///////////////////normal
        delay(500);
        Serial.println("Power outage");
        delay(500);
        Line_Notify(bat);
    }   else if (digitalRead(SW) == LOW && digitalRead(SW2) == HIGH) {
        delay(500);
        Serial.println("Optical link failed !! The system will alert again within 45 minutes if the fiber cable still cannot be used");
        Line_Notify(message);
      }   
        
        }
      
                                             

  if (digitalRead(SW) == LOW && digitalRead(SW2) == LOW) {
        delay(500);
        Serial.println("Power outage");
       
        if(digitalRead(SW) == HIGH && digitalRead(SW2) == LOW){                                                ///////////////////Power outage
        delay(500);
        Serial.println("Optical link connected");
        delay(500);
        Line_Notify(sys);
    }   else if (digitalRead(SW) == LOW && digitalRead(SW2) == HIGH) {
        delay(2500);
        Serial.println("Optical link failed !! The system will alert again within 45 minutes if the fiber cable still cannot be used");
        Line_Notify(message);
      }   
        
        }
      
                                       
 




   if (digitalRead(SW) == LOW && digitalRead(SW2) == HIGH) {
        delay(2500);
        Serial.println("Optical link failed !! The system will alert again within 45 minutes if the fiber cable still cannot be used");           ///////////////////Power outage
        Line_Notify(message);

        if(digitalRead(SW) == LOW && digitalRead(SW2) == LOW){
        delay(500);
        Serial.println("Power outage");
        delay(2500);
        Line_Notify(bat);
    }   else if (digitalRead(SW) == HIGH && digitalRead(SW2) == LOW){
        delay(500);
        Serial.println("Optical link connected");
        delay(2500);
        Line_Notify(sys);
      }   
        
        }
      
 }


void Line_Notify(String message) {
  axTLS::WiFiClientSecure client; 

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  // Serial.println(req);
  client.print(req);

  delay(20);

  // Serial.println("-------------");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  // Serial.println("-------------");
}
