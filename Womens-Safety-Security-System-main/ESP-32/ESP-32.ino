
#include <TinyGPSPlus.h>
#include <ESPDateTime.h>

//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <WiFi.h>
#include <HTTPClient.h>

int buzzer = 25;//BUZZER SECTION
const char* ssid = "yash";
const char* password = "12345678";

const char* serverName = "http://maker.ifttt.com/trigger/alert_text/with/key/k0jk3AGxT7V_hywudfBzhzE8btgMzE4230Opa3O8e8P";

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void setup() {
  Serial.begin(115200);

  // put your setup code here, to run once:
  pinMode(buzzer,OUTPUT);//BUZZER SECTION


  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");

  // Random seed is a number used to initialize a pseudorandom number generator
  randomSeed(analogRead(0));
}


void loop() {
  //BUZZER SECTION
// put your main code here, to run repeatedly:
  
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(1000);
  // Send an HTTP POST request every 10 seconds
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
 
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      
      String latitude = String(Serial.readString());
      String longitude = String(Serial.readString());
      
      String httpRequestData = "value1=" + latitude+ "&value2=" + longitude;
      int httpResponseCode = http.POST(httpRequestData);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }

}
