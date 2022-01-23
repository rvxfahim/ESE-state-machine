import socket
s = socket.socket()        # Create a socket object         
s.bind(('0.0.0.0', 8090 )) # Bind to the port
# Returns true if the request was successful.
s.listen(0)             # Now wait for client connection.              
#  Returns true if the request was successful.
while True:
 
    #  Accept a client and addr.
    client, addr = s.accept()   
 
    while True:
                # Receive 32 bytes from the server
        content = client.recv(32)
 
        #  Ensure content is a byte string.
        if len(content) ==0:
           break
 
        else:
            #print on terminal that message is received from client
            print("Message received from client: " + content.decode())
            #print address of client
            print("Client address: " + str(addr))
    #print("Closing connection")
    client.close()