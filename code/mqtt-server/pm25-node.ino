#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Your Wifi SSID"; // Enter your WiFi name
const char* password =  "WIFI password"; // Enter WiFi password
const char* mqttServer = "mqtt server ip address";
const int mqttPort = 1883;
const char* mqttUser = "mqtt user";
const char* mqttPassword = "mqtt password";
 
WiFiClient espClient;
PubSubClient client(espClient);

#include <SoftwareSerial.h>

#include <Wire.h>
#include <Adafruit_MLX90614.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

SoftwareSerial mySerial(D8,D7); // RX, TX
unsigned int pm1 = 0;
unsigned int pm2_5 = 0;
unsigned int pm10 = 0;
int i = 0;
int IRpin = D0;
int buzzpin = D3;
int led_G = D5;
int led_R = D6;

bool IR = 1;
bool lastIR = 1;
float adj = 4.5;
float temp = 38;
float Ambient = 0;
float Object = 00;

void setup() {
  Serial.begin(9600);
  while (!Serial) ;
  mySerial.begin(9600);
  mlx.begin();
  pinMode(buzzpin, OUTPUT);
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("     start");


  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("temi4", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  client.publish("temi4", "start"); //Topic name
  client.subscribe("esp/test");
  LCD("Object   ",9999);
}

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

void LCD_lol() {
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.print("!!!!!!");
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
      Serial.print("{ ");
      Serial.print("pm1: ");
      Serial.print(pm1);
      Serial.print(" ug/m3");
      Serial.print(", ");
    }
    else if (index == 7) {
      pm2_5 = 256 * previousValue + value;
      Serial.print("pm2.5: ");
      Serial.print(pm2_5);
      Serial.print(" ug/m3");
      Serial.print(", ");
    }
    else if (index == 9) {
      pm10 = 256 * previousValue + value;
      Serial.print("pm10: ");
      Serial.print(pm10);
      Serial.print(" ug/m3");
    }
    else if (index > 15) {
      break;
    }
      index++;
  }
  while (mySerial.available()) mySerial.read();
  Serial.println(" }");
}

void bodytemp() {
  //Ambient = mlx.readAmbientTempC();
  Object = mlx.readObjectTempC() + adj;
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

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
}

void buzz_song(int t) {
  digitalWrite(buzzpin, HIGH);
  delay(t);
  digitalWrite(buzzpin, LOW);
  delay(t/3);
}
void Led(bool R, bool G) {
  digitalWrite(led_R, R);
  digitalWrite(led_G, G);
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
    //LCD("Temperature   ",9999);
    LCD("              ",9999); 
    Led(0,0);
  }
  else if (i%24 == 0) bodytemp();
  if (i%20 == 0) pm();
  if (i == 60) {
    client.publish("temi4", ("pm2.5: " + String(pm2_5) + " ug/m3").c_str(), true);
    client.publish("temi4", ("Ambient: " + String(mlx.readAmbientTempC()) + " C").c_str(), true);
    Serial.println("Ambient: " + String(mlx.readAmbientTempC()) + " C");
    Serial.println("Object : " + String(Object) + " C");
    Serial.println("------- MQTT -------");
    i = 0;
  }
  delay(100);
}
