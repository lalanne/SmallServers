
import socket
import sys

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # IPV4 and TCP
    print 'Socket Created'

except socket.error, msg:
    print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1]
    sys.exit();

remote_ip = '127.0.0.1'
remote_port = 4040

s.connect((remote_ip, remote_port))
print 'Socket connected to ' + remote_ip + ' on ip ' + remote_ip

message = '<?xml version="1.0" encoding="ISO-8859-1"?>' + \
        '<msg>' + \
            '<header id_trans="1111" app="xml" user="ussd" passw="ussd" action="1"/>' + \
            '<req>' + \
                '<op>req_comp_promo</op>' + \
                '<msisdn>' + sys.argv[1] + '</msisdn>' + \
                '<idPromo>BO_80MB_2D</idPromo>' + \
            '</req>' + \
        '</msg>'

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

