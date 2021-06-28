#include <SoftwareSerial.h>

#include <Wire.h>
#include <Adafruit_MLX90614.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define IRpin D0
#define buzzpin D3
#define led_G D5
#define led_R D6

SoftwareSerial mySerial(D8,D7); // RX, TX
unsigned int pm1 = 0;
unsigned int pm2_5 = 0;
unsigned int pm10 = 0;
int i = 0;


bool IR = 1;
bool lastIR = 1;
float adj = 4.5;
float temp = 38;
float Ambient = 0;
float Object = 00;

void LCD(String T1 ,float Data) {
  lcd.setCursor(2, 0);
  lcd.print(T1);
  if (Data != 9999) {
    lcd.setCursor(1, 1); 
    lcd.print("    ");
    lcd.setCursor(4, 1);
    lcd.print(Data);
    lcd.setCursor(9, 1); 
    lcd.print(" C    ");
  }
  else {
    lcd.setCursor(1, 1);
    lcd.print("Put your hand");
  }
}

void pm() {
  int index = 0;
  char value;
  char previousValue;

  while (mySerial.available()) {
    value = mySerial.read();
    if ((index == 0 && value != 0x42) || (index == 1 && value != 0x4d)) {
      Serial.println("Cannot find the data header.");
      break;
    }

    if (index == 4 || index == 6 || index == 8 || index == 10 || index == 12 || index == 14) {
      previousValue = value;
    }
    else if (index == 5) {
      pm1 = 256 * previousValue + value;
      Serial.print("pm1: " + String(pm1) + " ug/m3, ");
    }
    else if (index == 7) {
      pm2_5 = 256 * previousValue + value;
      Serial.print("pm2.5: " + String(pm2_5) + " ug/m3, ");
    }
    else if (index == 9) {
      pm10 = 256 * previousValue + value;
      Serial.print("pm10: " + String(pm10) + " ug/m3");
    }
    else if (index > 15) {
      break;
    }
      index++;
  }
  while (mySerial.available()) mySerial.read();
  Serial.println(" ");
}

void Led(bool R, bool G) {
  digitalWrite(led_R, R);
  digitalWrite(led_G, G);
}

void buzz_song(int t) {
  digitalWrite(buzzpin, HIGH);
  delay(t);
  digitalWrite(buzzpin, LOW);
  delay(t/3);
}

void tempread(){
  Ambient = mlx.readAmbientTempC();
  Object = mlx.readObjectTempC() + adj;
}
void bodytemp() {
  tempread();
/*  Serial.print("Ambient = ");
  Serial.print(Ambient); 
  Serial.println("*C");
  Serial.print("Object = ");
  Serial.print(Object);
  Serial.println("*C");
*/
  LCD("Temperature   ",Object);
  if (Object > temp) {
    Serial.println("------------ !!!!! ------------");
    Led(1,0);
    delay(1000);
    buzz_song(700);
    buzz_song(700);
    //LCD_lol();
    buzz_song(600);
    //LCD("Temperature   ",Object);
    //delay(1000);
  }
  else {
    Led(0,1);
    delay(1300);
    buzz_song(120);
    buzz_song(120);
    delay(1700);
  }
}
