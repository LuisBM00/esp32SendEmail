#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "wifi id";
const char* pass = "wifi password";


const String WebhookURL = "url webhook"; 


void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, pass);

  Serial.println("Conectando...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connectado");
  Serial.println(WiFi.localIP());
}

void loop() {
  const int pinTouch = touchRead(T0);

  Serial.print("Value: ");
  Serial.println(pinTouch);

  if(pinTouch < 100 && pinTouch > 40){
    Serial.println("Touch detected: Enviando email");

    if(SendEmail(pinTouch)){
      Serial.println("Email enviado");
      Serial.println("Espera 5 segundos para tocar el pin");
      delay(5000);
    }else{
      Serial.println("An error has been ocurred, try again");
    }
  }

  delay(500);
}

bool SendEmail(int value){
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    http.begin(WebhookURL);
    http.addHeader("Content-Type", "application/json");

    String _value = "El valor detectado es: ";
    _value += value;

    const String json = "{\"value1\":\""+_value+"\"}"; 
    int httpResponseCode = http.POST(json);
    
    if(httpResponseCode >= 200 && httpResponseCode < 300)
    return true;
    else return false;
  }
}
