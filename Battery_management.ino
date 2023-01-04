#include <ESP8266WiFi.h>
#define NUMSAMPLES 10
int sum = 0;
unsigned char sample_count = 0;
float voltage = 0.0;
const char* ssid = "gok-ext";
const char* password ="secondfloor";
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "XS1KHB2W11L9E6PI";

void setup()
{
Serial.begin(9600);
delay(1000);
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
 {
  delay(500);
  Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
}

void loop()
{
while (sample_count < NUMSAMPLES)
{
 sum += analogRead(A0);
 sample_count++;
 delay(10);
 }
 voltage = ((float)sum / (float)NUMSAMPLES * 5.015) / 1024.0;
 float cell1=(voltage * 11.132);
 Serial.print("total voltage=");
 Serial.println(cell1);
 delay(1000);
 sample_count = 0;
 sum = 0;
 
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
return;
 }
 String url = "/update?key=";
 url+=writeAPIKey;
 url+="&field1=";
 url+=float(cell1);
 url+="\r\n";
client.print(String("GET ") + url + " HTTP/1.1\r\n" +
"Host: " + host + "\r\n" +
"Connection: close\r\n\r\n");
 Serial.print("total voltage:");
 Serial.print(cell1);
 Serial.print("\n");
Serial.println("Send to ThingSpeak.\n");
client.stop();
 Serial.println("Wait for 15 sec to update next datapack in thingSpeak");
delay(1000);
}
