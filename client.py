#Create a socket

import socket
import sys

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #IPV4 and TCP
    print 'Socket Created'

except socket.error, msg:
    print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1]
    sys.exit();

remote_ip = '127.0.0.1'
remote_port = 4040

s.connect((remote_ip, remote_port))
print 'Socket connected to ' + remote_ip + ' on ip ' + remote_ip

message = '093029i0klfjwlkfjlwkjkjqfoijwoefijoiejwf'

try :
    s.sendall(message)
except socket.error:
    print 'Send failed'
    sys.exit()
 
print 'Message send successfully'

#Now receive data
reply = s.recv(4096)
 
print 'message from server[' + reply + ']'

s.close()

