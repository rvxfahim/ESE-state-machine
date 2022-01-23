#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long timer = 0;
unsigned long timer2 = 0;
unsigned long timer3 = 0;
unsigned long timer4 = 0;
const char *ssid = "honeygain";
const char *password = "thabramu";
int retry = 0;
const uint16_t port = 8090;
const char *host = "192.168.1.22";
String state2;
AsyncWebServer server(80);
AsyncWebSocket ws("/test");
WiFiClient client;
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{

  if (type == WS_EVT_CONNECT)
  {

    Serial.println("Websocket client connection received");
  }
  else if (type == WS_EVT_DISCONNECT)
  {
    Serial.println("Client disconnected");
  }
  else if (type == WS_EVT_DATA)
  {

    //Serial.println("Data received: ");
    //print received json data
    for (int i = 0; i < len; i++)
    {
      //Serial.print((char)data[i]);
    }
    //append uint data to string
    String dataString = "";
    for (int i = 0; i < len; i++)
    {
      dataString += (char)data[i];
    }
    //dataString contains json data about X and Y
    //decode json data
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, dataString);
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    //get X and Y values from json
    String x = doc["x"];
    String y = doc["y"];
    //if doc has key state, set state2 to value of state
    if (doc.containsKey("state"))
    {
      String state = doc["state"];
      state2 = state;
      Serial.println(state2);
    }
    //print x and y values
    Serial.println("Leader sent: ");
    Serial.print("X: ");
    Serial.println(x);
    Serial.print("Y: ");
    Serial.println(y);
  }
}
void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();
}
//make a function to send a message to the client
void sendMessage(String message)
{
  client.print(message);
}
void loop()
{
  //retry count

  bool connected = false;
  if (!client.connect(host, port))
  {

    Serial.println("Connection to host failed");
    //retry count
    retry++;
    //if retry count is greater than 5, exit
    if (retry > 5)
    {
      Serial.println("Exiting");
      connected = false;
      return;
    }
  }
  else
  {
    connected = true;
    Serial.println("Connected to host");
    connected = true;
    //Serial.println("Connected to server successful!");
    //generate random x and y coordinates for server
    int x = random(0, 100);
    int y = random(0, 100);
    //generate random speed value for server
    int speed = random(0, 100);
    //generate json data
    String json = "{\"x\":" + String(x) + ",\"y\":" + String(y) + ",\"speed\":" + String(speed) + "}";
    //send json data to server
    sendMessage(json);
  }
  if(state2=="lost connection"){
    timer3 = millis();
    timer4 = millis();
    timer2 = millis();
    timer = millis();
    while (state2=="lost connection")
    {
      //start timer3
      timer3 = millis();
      if (timer3-timer4>5000)
      {
        //5 seconds has ellapsed in lost connection state
        //blink leds slower
        timer2=millis();
        if (timer2-timer>2000)
        {
          //2000ms has ellapsed
          //toggle led
          timer=millis();
          digitalWrite(2, !digitalRead(2));
          Serial.println("initiating emergency stop");
        }
        
        
      }
      else
      {
        //blink leds faster
        timer2=millis();
        if (timer2-timer>300)
        {
          //300ms has ellapsed
          //toggle led
          timer=millis();
          digitalWrite(2, !digitalRead(2));
        }
      }
      
    }
    
  }
  if(state2=="got connection")
  {
    digitalWrite(2, LOW);
  }
  delay(1000);
}