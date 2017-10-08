
from Configuration import NetworkConfig
from ResponseBuilder import Response
from Parser import Parser
import socket
import sys
import threading

ALLOWED_NUMBER_OF_ARGUMENTS = 3
SUCCESS = 0
IP_POSITION = 1
PORT_POSITION = 2
NUMBER_OF_BYTES_RECEIVED = 1024
BACKLOG_CONNECTIONS = 10
INFINITE_LOOP = 1


def handle_connection(connection, message):
    msisdn = Parser(message).msisdn()
    response = str(Response(msisdn.text).build())

    if response != 'no response':
        connection.sendall(response)
#    conn.close()


if(len(sys.argv) != ALLOWED_NUMBER_OF_ARGUMENTS):
    print 'ERROR: Wrong Number of arguments!!!'
    exit(SUCCESS)

networkConfig = NetworkConfig(sys.argv[IP_POSITION], sys.argv[PORT_POSITION])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
try:
    s.bind(networkConfig.connection_data())
except socket.error, msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()


while 1:
    # backlog = 10, if incoming an 11th
    # connection the request should be rejected
    s.listen(BACKLOG_CONNECTIONS)

    conn, addr = s.accept()  # blocking call
    # print 'Connected with ' + addr[0] + ':' + str(addr[1])

    msg = conn.recv(NUMBER_OF_BYTES_RECEIVED)
    print msg

    t = threading.Thread(target=handle_connection, args=(conn, msg,))
    t.start()
    # print 'active threads[' + str(threading.activeCount()) + ']'


s.close()
