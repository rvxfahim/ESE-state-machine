import time
import websocket
import json
ws = websocket.WebSocket()
ws.connect("ws://192.168.1.2/test")
#send a json message
message = "lost connection"
#format message to json
message = json.dumps({"state":message})
#send message
ws.send(message)