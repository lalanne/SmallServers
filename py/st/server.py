
from Configuration import NetworkConfig
from ResponseBuilder import Response
from Parser import Parser
import socket
import sys

SUCCESS = 0
FAIL = 1

IP_POSITION = 1
PORT_POSITION = 2
LOG_OPTION_POSITION = 3
NUMBER_OF_BYTES_RECEIVED = 1024
BACKLOG_CONNECTIONS = 10
INFINITE_LOOP = 1
NUMBER_OF_ARGUMENTS_LOG_OPTION = 4
NUMBER_OF_ARGUMENTS_NO_LOG_OPTION = 3
LOG_ON = "on"
LOG_OFF = "off"


def handle_connection(connection, message):
    msisdn = Parser(message).msisdn()
    response = str(Response(msisdn.text).build())

    if response != 'no response':
        connection.sendall(response)
    conn.close()


if(len(sys.argv) < NUMBER_OF_ARGUMENTS_NO_LOG_OPTION and
        len(sys.argv) > NUMBER_OF_ARGUMENTS_LOG_OPTION):
    print 'ERROR: Wrong Number of arguments!!!'
    exit(FAIL)

logs = False

if(len(sys.argv) == NUMBER_OF_ARGUMENTS_LOG_OPTION):
    if(sys.argv[LOG_OPTION_POSITION] == LOG_ON):
        logs = True
    elif(sys.argv[LOG_OPTION_POSITION] == LOG_OFF):
        logs = False
    else:
        print 'ERROR: wrong log option!!!'
        exit(FAIL)


networkConfig = NetworkConfig(sys.argv[IP_POSITION], sys.argv[PORT_POSITION])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.bind(networkConfig.connection_data())
except socket.error, msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()

# backlog = 10, if incoming an 11th connection the request should be rejected
s.listen(BACKLOG_CONNECTIONS)
while INFINITE_LOOP:
    conn, addr = s.accept()  # blocking call
    # print 'Connected with ' + addr[0] + ':' + str(addr[1])

    msg = conn.recv(NUMBER_OF_BYTES_RECEIVED)
    if(logs):
        print msg

    handle_connection(conn, msg)


s.close()
