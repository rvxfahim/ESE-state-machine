import time
import websocket
import json
ws = websocket.WebSocket()
ws.connect("ws://192.168.1.2/test")
ws.send("Test")
#send a json message
while True:
    #random x y cordinates
    x = int(time.time()*1000)
    y = int(time.time()*1000)
    #create a json message
    message = json.dumps({"x":x,"y":y})
    #check if connection is still open
    if ws.connected:
        #send the message
        ws.send(message)
        #print the message
        print(message)
    else:
        #retry connection
        ws.connect("ws://192.168.1.2/test")
        #print retrying connection
        print("Retrying connection")
    time.sleep(2)