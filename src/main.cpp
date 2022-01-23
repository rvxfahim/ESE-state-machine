#include <WiFi.h>
#include "ESPAsyncWebServer.h"
const char *ssid = "honeygain";
const char *password = "thabramu";

const uint16_t port = 8090;
const char *host = "192.168.1.22";
String state = "decoupled";
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

    Serial.println("Data received: ");

    for (int i = 0; i < len; i++)
    {
      Serial.print((char)data[i]);
    }

    Serial.println();
  }
}
void setup()
{

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
  

  if (!client.connect(host, port))
  {

    Serial.println("Connection to host failed");

    delay(1000);
    return;
  }

  Serial.println("Connected to server successful!");

  delay(1000);
}