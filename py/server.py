
from Configuration import NetworkConfig
from ResponseBuilder import Response
from Parser import Parser
import socket
import sys


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.bind(NetworkConfig().connection_data())
except socket.error, msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()

# backlog = 10, if incoming an 11th connection the request should be rejected
s.listen(10)
while 1:
    conn, addr = s.accept()  # blocking call
    print 'Connected with ' + addr[0] + ':' + str(addr[1])

    msg = conn.recv(1024)
    print 'receiving: [' + msg + ']'

    msisdn = Parser(msg).msisdn()
    print 'msisdn: [' + str(msisdn.text) + ']'

    response = Response(msisdn.text).build()
    data = str(response)

    if not data:
        break

    if data != 'no response':
        conn.sendall(data)

conn.close()
s.close()
