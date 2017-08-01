
from Configuration import NetworkConfig
from ResponseBuilder import Response
from Parser import Parser
import socket
import sys
import threading


def handle_connection(connection, message):
    msisdn = Parser(message).msisdn()
    response = str(Response(msisdn.text).build())

    if response != 'no response':
        connection.sendall(response)
#    conn.close()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
try:
    s.bind(NetworkConfig().connection_data())
except socket.error, msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()


while 1:
    # backlog = 10, if incoming an 11th connection the request should be rejected
    s.listen(10)

    conn, addr = s.accept()  # blocking call
    print 'Connected with ' + addr[0] + ':' + str(addr[1])

    msg = conn.recv(1024)
    print 'receiving: [' + msg + ']'

    t = threading.Thread(target=handle_connection, args=(conn, msg,))
    t.start()
    print 'active threads[' + str(threading.activeCount()) + ']'


s.close()
