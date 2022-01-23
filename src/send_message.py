import time
import websocket
import json
ws = websocket.WebSocket()
ws.connect("ws://192.168.1.2/test")

ws.send("Test")
#send a json message
while True:
    ws.send(json.dumps({"message": "Jsoned message"}))
    time.sleep(2)