import socket
import json
s = socket.socket()     
s.bind(('0.0.0.0', 8090 )) 
s.listen(0)
while True:
    #  Accept a client and addr.
    client, addr = s.accept()   
 
    while True:
                # Receive 32 bytes from the server
        data = client.recv(32)
 
        #  Ensure content is a byte string.
        if len(data) ==0:
           break
 
        else:
            #print on terminal that message is received from client
            #deserialize data
            data = json.loads(data)
            #data contains x and y cordinates and speed
            x = data["x"]
            y = data["y"]
            speed = data["speed"]
            #print the data received from client
            print("following truck says: x = {}, y = {}, speed = {}".format(x,y,speed))
            #print address of client
            print("Client address: " + str(addr))
    #print("Closing connection")
    client.close()