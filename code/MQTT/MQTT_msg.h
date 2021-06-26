#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "xxxxx"; // Enter your WiFi name
const char* password =  "xxxxx"; // Enter WiFi password
const char* mqttServer = "xxxxx";
const int mqttPort = xxxxx;
const char* mqttUser = "xxxxx";
const char* mqttPassword = "xxxxx";

WiFiClient espClient;
PubSubClient client(espClient);

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

void setMqtt(){
  while (!Serial) ;
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
}
void mqtt_msg(String Text){
  client.publish("temi4", (Text).c_str(), true);
  //client.publish("temi4", ("Ambient: " + String(mlx.readAmbientTempC()) + " C").c_str(), true);
}
