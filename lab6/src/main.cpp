#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT11  

const char* ssid = "ฤกษ์ที่ดี ค";         //ค่าของ SSID (อย่าลืมแก้เป็น ชื่อ SSID ของตัวเอง)
const char* password = "12345678"; //ค่าของ SSID (อย่าลืมแก้เป็น password ของตัวเอง)

WiFiServer server(80);

const int DHTPin = D1;
DHT dht(DHTPin, DHTTYPE);
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  delay(10);
  dht.begin();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();  // Starting the web server
  Serial.println("Start Webserver, Waiting for the IP Address...");
  delay(10000);
  Serial.println(WiFi.localIP());
}

void loop() {
 
  WiFiClient client = server.available(); //wait new client
  
  if (client) {
    Serial.println("New client");
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n' && blank_line) {
            float h = dht.readHumidity();
            float t = dht.readTemperature();
            float f = dht.readTemperature(true);
            if (isnan(h) || isnan(t) || isnan(f)) {
              Serial.println("Failed to read from DHT sensor!");   
            }
            else{
              Serial.print("Humidity: ");
              Serial.print(h);
              Serial.print(" %\t Temperature: ");
              Serial.print(t);
              Serial.print(" *C ");
              Serial.print(f);
              Serial.print(" *F");
            }
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
  
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head></head><body><h1>Hello IoT & IT World</h1><h3>Temperature in this room: ");
            client.println(t);
            client.println("*C</h3><h3>Temperature in Fahrenheit: ");
            client.println(f);
            client.println("*F</h3><h3>Humidity: ");
            client.println(h);
            client.println("%</h3>");
            client.println("</body></html>");     
            break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }  
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}   
