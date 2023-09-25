#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define LED_PIN D2 //ขาที่ต่อกับ LED
#define DHTPIN D1   //ขาที่ต่อเซนเซอร์ DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "DISEZ_2.4G"; //อย่าลืมแก้ไข SSID ของ WIFI ที่จะให้ NodeMCU ไปเชื่อมต่อ
const char* password = "0915594555"; //อย่าลืมแก้ไข PASSWORD ของ WIFI
const char* mqtt_server = "broker.netpie.io"; 
const int mqtt_port = 1883;
const char* mqtt_Client = "2f1d14eb-27ed-409f-9caf-e4f57f730cff";  //อย่าลืมแก้ไข ClientID
const char* mqtt_username = "cNUBFiSyLgJiWP61RDB3a5TrTSmgHbM1";  //อย่าลืมแก้ไข Token
const char* mqtt_password = "XwSa2F2gAFaXyKk29BNutRHnymAAZNpk"; //อย่าลืมแก้ไข Secret

WiFiClient espClient; 
PubSubClient client(espClient);

long lastMsg = 0;
int value = 0;
char msg[100];

int ledState = 0;

String DataString;

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
  if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) { //เชื่อมต่อกับ MQTT BROKER
    Serial.println("connected");
    client.subscribe("@msg/operator");
  }
  else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println("try again in 2.5 seconds");
    delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  for (int i = 0; i < length; i++) {
    message = message + char(payload[i]);
    
  }
  Serial.println(message);
  if(String(topic) == "@msg/operator") {
    int val;
    if (message == "ON"){
      digitalWrite(LED_PIN,HIGH);
      ledState = 1;
      client.publish("@shadow/data/update", "{\"data\" : {\"led\" : \"1\"}}");
      Serial.println("LED ON"); }
    else if (message == "OFF") {
      ledState = 0;
      digitalWrite(LED_PIN,LOW);
      client.publish("@shadow/data/update", "{\"data\" : {\"led\" : \"0\"}}");
      Serial.println("LED OFF"); }
    } 
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN,OUTPUT);
  pinMode(A0, INPUT);
  dht.begin();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //เชื่อมต่อกับ WIFI
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //เชื่อมต่อกับ WIFI สำเร็จ แสดง IP
  client.setServer(mqtt_server, mqtt_port); //กำหนด MQTT BROKER, PORT ที่ใช้
  client.setCallback(callback); //ตั้งค่าฟังก์ชันที่จะทำงานเมื่อมีข้อมูลเข้ามาผ่านการ Subscribe
  client.subscribe("@msg/operator");
  ledState = 0;
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 2500) { //จับเวลาส่งข้อมูลทุก ๆ 3 วินาที
    lastMsg = now;
    ++value;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    int ldr = analogRead(A0);
    DataString = "{\"data\":{\"temperature\":"+(String)t+",\"humidity\":"+(String)h+",\"ldr\":"+(String)ldr+",\"led\":"+(String)ledState+"}}"; 
    // Example of data : {"data":{"temperature":25 , "humidity": 60}}
    DataString.toCharArray(msg, 100);
    Serial.println("Hello NETPIE2020");
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("@shadow/data/update", msg); //ส่งข้อมูลไปยัง Real Time Database (Shadow)
  }
  delay(1);
}
