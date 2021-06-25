#include <ESP8266WiFi.h>
#include "Data.h"
#include "MQTT_msg.h"

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(0); 
  
  Serial.println("/nstart");
  while (!Serial) ;
  mySerial.begin(9600);
  mlx.begin();
  pinMode(buzzpin, OUTPUT);
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("     start");
  LCD("Object   ",9999);
}

void loop() {
  IR = digitalRead(IRpin);
  if (IR != lastIR){
    delay(70);
    if (digitalRead(IRpin) == 0){
      buzz_song(400);
      buzz_song(200);
      buzz_song(100);
      bodytemp();
    }
    else digitalWrite(buzzpin, LOW);
    //bodytemp();
  }
  lastIR = IR;

  i++;
  if (IR != 0) {
    LCD("              ",9999); 
    Led(0,0);
  }
  else if (i%24 == 0) bodytemp();
  
  if (i%20 == 0) pm();
  if (i == 60) {
    tempread();
    mqtt_msg("Ambient: " + String(Ambient) + " C \npm2.5: " + String(pm2_5) + " ug/m3");
    Serial.println("------- MQTT -------");
    i = 0;
  }
  delay(50);
}
