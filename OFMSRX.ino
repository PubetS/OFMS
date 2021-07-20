/* drawString example sketch: display strings all over the place */
#define pulse_ip 22
int ontime,offtime,duty;
float freq,period;



#include <SPI.h>
#include <stdint.h>
#include <TFTv2.h>

void setup() {
    pinMode(49,OUTPUT);\
    pinMode(47,OUTPUT);
    pinMode(pulse_ip,INPUT);
    Serial.begin(9600);
    
    TFT_BL_ON;      // turn on the background light
    Tft.TFTinit();  // init TFT library
    Tft.fillScreen(0, 240, 0, 320, CYAN);
    Tft.fillScreen(10, 230, 5, 315, BLACK);
    
    TextOrientation orientation;
    orientation = LANDSCAPE;
    Tft.drawString("OPTICAL FIBER", 35, 190, 3, WHITE, orientation);
    Tft.drawString("MONITORING SYSTEM", 5, 150, 3, WHITE, orientation);
    Tft.drawString("Optical link Status : ", 40,100, 2, WHITE, orientation);
    

}

void loop() {
     

    
   ontime = pulseIn(pulse_ip,HIGH);  // freq math
   offtime = pulseIn(pulse_ip,LOW);
   period = ontime+offtime;
   freq = 1000000.0/period;
   duty = (ontime/period)*100;

    if (freq > 7000 && freq < 15000){
      Tft.fillScreen(50, 80, 15, 305, BLACK);
      Tft.drawString("Power outage", 80,50, 2,YELLOW,LANDSCAPE);
      delay(2000);
      Serial.println("Power outage");
      Serial.println(freq);
      digitalWrite(49,LOW);
      digitalWrite(47,LOW);
      
  
      } else if (freq > 17000 && freq < 25000){
         Tft.fillScreen(50, 80, 15, 305, BLACK);
        Tft.drawString("Optical link connected", 30,50, 2, GREEN,LANDSCAPE);
        delay(2000);
        Serial.println("Optical link connected");
        Serial.println(freq);
        digitalWrite(49,HIGH);
        digitalWrite(47,LOW);
        
       
 
        }else {
          Tft.fillScreen(50, 80, 15, 305, BLACK);
          Tft.drawString("Optical link failed", 50,50, 2, RED,LANDSCAPE);
          delay(2000);
          Serial.println("Optical link failed");
          Serial.println(freq);
          digitalWrite(49,LOW);
          digitalWrite(47,HIGH);
         
      
          }

}

   
