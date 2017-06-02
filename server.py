#Open a socket
#Bind to an address(port)
#Listen for incoming connections
#Accept connections
#Read(receive) and response(send)

import socket
import sys

IP = '127.0.0.1'
PORT = 4040

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

try:
    s.bind((IP, PORT))
except socket.error, msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()

print 'Socket bind complete'

s.listen(10) #backlog = 10, if incoming an 11th connection the request should be rejected
print 'Now socket is listening'

while 1:
    conn, addr = s.accept()  #blocking call
    print 'Connected with ' + addr[0] + ':' + str(addr[1])

    data = conn.recv(1024)

    print 'receiving: [' + data + ']'

    data += '[from the server]'

    if not data: 
        break

    conn.sendall(data)
     
conn.close()
s.close()


