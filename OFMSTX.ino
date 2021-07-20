 int sender_code = 1;
int receive_Power =5; 



void setup() {
  pinMode(receive_Power,INPUT);
  pinMode(sender_code,OUTPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop() {
  
  if(digitalRead( receive_Power)==1)
    {
        tone(12,20000);                //ส่ง20kHzและแสดงLEDสีเขียวที่ขา10   ต่อไฟบ้าน 
        digitalWrite(7,LOW);
        digitalWrite(10,HIGH);
       
    }

   if(digitalRead( receive_Power)==0)
     {
        tone(12,10000);              //ส่ง10kHzและแสดงLEDสีเหลืองที่ขา7   ต่อไฟแบตเตอรี่
        digitalWrite(7,HIGH);
        digitalWrite(10,LOW);
        ;
      
    }
}


     
