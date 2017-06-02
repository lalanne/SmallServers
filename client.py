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


