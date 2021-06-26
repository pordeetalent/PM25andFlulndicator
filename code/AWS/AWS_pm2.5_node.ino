#include <ESP8266WiFi.h>
#include "random.h"
#include "global.h"
#include "aws.h"
#include "Data.h"

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("     start");
  Serial.setDebugOutput(0); 
  generateClientID();
  init_AWS_service();
  
  Serial.println("/nstart");
  while (!Serial) ;
  mySerial.begin(9600);
  mlx.begin();
  pinMode(buzzpin, OUTPUT);
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);

  LCD("         ",9999);
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
     set_wifi();
     AWS_Setup();
  }
  AWS_callback();
  
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

  if (i%100 == 0) pm();
  if (i == 600) {
    tempread();
    AWS_msg("Ambient: " + String(Ambient) + " C \npm2.5:\t " + String(pm2_5) + " ug/m3");
    //AWS_msg("Object : " + String(Object) + " C");
    AWS_callback();
    Serial.println("------- AWS -------");
    i = 0;
  }
  delay(100);
}
