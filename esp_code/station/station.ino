#include <HTTPClient.h>
#include "esp_wifi.h"
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "ARCL";
// const char* password = "b337H0v3N";
const char* password = "beethoven";

int mpin1 = 22;
int mpin2 = 23;
int en_pin = 14;
int rainDigital = 18;
int sensorPin = 34;
int threshold = 140;
String currentState = "1";

String hostname = "ESP32";

const int freq = 30000;
const int pwmC = 0;
const int resolution = 1;
int dutyCycle = 200;

String url;

// wifi_sta_list_t wifi_sta_list;
// wifi_sta_list_t wifi_sta_list_empty;
// tcpip_adapter_sta_list_t adapter_sta_list;
// tcpip_adapter_sta_list_t adapter_sta_list_empty;
//
// char str_ip[16];

String ip = "192.168.101.118";
String port = "8081";
// String port = "5000";

void initWiFi() {
  Serial.print("Setting AP...");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname.c_str());  //define hostname
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("Setup done");
}

String httpGETRequest(const char* serverUrl) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverUrl);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.print("API result");
    Serial.println(http.getString());
  }
  http.end();
  return http.getString();
}

void setup() {
  Serial.begin(115200);
  pinMode(mpin1, OUTPUT);
  pinMode(mpin2, OUTPUT);
  pinMode(en_pin, OUTPUT);

  pinMode(rainDigital,INPUT);


  ledcSetup(pwmC, freq, resolution);
  ledcAttachPin(en_pin, pwmC);
  ledcWrite(pwmC, dutyCycle);

  initWiFi();
}

void loop() {

  // digitalWrite(mpin1, LOW);
  // digitalWrite(mpin2, HIGH);
  // delay(2000);
  digitalWrite(mpin1, LOW); // code to run the motor
  digitalWrite(mpin2, LOW);

  int rainDigitalVal = digitalRead(rainDigital);
  // Serial.println(rainDigitalVal);

  int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor

  int outputValue = map(sensorValue, 0, 4095, 0, 255); // map the 10-bit data to 8-bit data

  Serial.println(outputValue);

  if(outputValue <= threshold){
    //rain detected
    
    url = "http://" + ip + ":" + port + "/set/sensor/1";
    Serial.println("Calling url " + url);
    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();
    String out = http.getString();
    Serial.println("Output : " + out);

  }
  else{
  //rain not detected
    url = "http://" + ip + ":" + port + "/set/sensor/0";
    Serial.println("Calling url " + url);
    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();
    String out = http.getString();
    delay(1000);
  }
    url = "http://" + ip + ":" + port + "/get/command";
    Serial.println("Calling url " + url);
    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();
    String out = http.getString();
    Serial.println("Output : " + out);

    if(out.equals(currentState))
    {
      
    }
    else
    {
      if(currentState.equals("0"))
      {
        
          digitalWrite(mpin1, HIGH); // code to run the motor
          digitalWrite(mpin2, LOW);
          delay(5000);
  
        currentState = "1";
      }
      else
      {
          
      digitalWrite(mpin1, LOW); // code to run the motor
      digitalWrite(mpin2, HIGH);
      delay(5000);

      currentState = "0";
      }
     
    }

    digitalWrite(mpin1, LOW); // code to run the motor
    digitalWrite(mpin2, LOW);
    delay(200);
}