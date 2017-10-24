
from Configuration import NetworkConfig
from ResponseBuilder import Response
from Parser import Parser
import socket
import sys
import threading

SUCCESS = 0
FAIL = 1

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


if(len(sys.argv) < 3 and len(sys.argv) > 4):
    print 'ERROR: Wrong Number of arguments!!!'
    exit(FAIL)

logs = False

if(len(sys.argv) == 4):
    if(sys.argv[3] == "on"):
        logs = True
    elif(sys.argv[3] == "off"):
        logs = False
    else:
        print 'ERROR: wrong log option!!!'
        exit(FAIL)

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
    if(logs):
        print msg

    t = threading.Thread(target=handle_connection, args=(conn, msg,))
    t.start()
    # print 'active threads[' + str(threading.activeCount()) + ']'


s.close()
