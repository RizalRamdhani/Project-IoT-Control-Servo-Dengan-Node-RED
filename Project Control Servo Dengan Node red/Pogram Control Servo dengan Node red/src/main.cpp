#include <WiFi.h> 
#include <PubSubClient.h> 
#include <ESP32Servo.h> 
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
 void callback(char* topic, byte* payload, unsigned int length);
Servo myservo;// servo onject 
const char* ssid = "MAKERINDO2"; 
const char* password = "makerindo2019"; 
const char* mqtt_server = "broker.hivemq.com";// MQTT broker 
WiFiClient espClient; 
PubSubClient client(espClient); 
long lastMsg = 0; 
char msg[50]; 
int value = 0;

void setup() { 
Serial.begin(115200); 
myservo.attach(4); 
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
client.setServer(mqtt_server, 1883); 
client.setCallback(callback); 
}
void callback(char* topic, byte* payload, unsigned int length) { 
String string; 
Serial.print("Message arrived ["); 
Serial.print(topic); 
Serial.print("] "); 
for (int i = 0; i < length; i++) { 
string+=((char)payload[i]); 
} 
Serial.print(string); 
if (topic = "/ThinkIOT/Servo-nodered/bro") /// esp32 subscribe topic  
Serial.print(" "); 
int status = string.toInt(); 
int pos = map(status, 1, 100, 0, 180); 
Serial.println(pos); 
myservo.write(pos); 
delay(15); 
}

void reconnect() { 
while (!client.connected()) { 
Serial.print("Attempting MQTT connection..."); 
if (client.connect("ESPClient")) { 
Serial.println("connected"); 
client.subscribe("/ThinkIOT/Servo-nodered/bro"); 
} else { 
Serial.print("failed, rc="); 
Serial.print(client.state()); 
Serial.println(" try again in 5 seconds"); 
delay(5000); 
}}} 
void loop() { 
if (!client.connected()) { 
reconnect(); 
} 
client.loop(); 
delay(100);
}
