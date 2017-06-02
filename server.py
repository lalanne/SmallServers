
import socket
import sys
import xml.etree.ElementTree as ET


RSLT_EXITO = 0
RSLT_ERR_PROMO_INEXISTENTE = 4
RSLT_ERR_SIN_SALDO_PP = 14
RSLT_ERR_TIPO_CLIENTE_DST = 18


def build_base_message(msisdn, result):
    message = '<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n' + \
        '<msg>\n\t' + \
        '<header action=\"1\" id=\"1111\"  />\n\t' + \
        '<resp>\n\t\t' + \
        '<op>rslt_comp_promo</op>\n\t\t' + \
        '<msisdn>' + str(msisdn) + '</msisdn>\n\t\t' + \
        '<result>' + str(result) + '</result>\n\t\t' + \
        '<strresult>OK</strresult>\n\t' + \
        '</resp>\n' + \
        '</msg>\n'
    return message


def build_response(msisdn):
    print '[build_response] msisdn[' + msisdn + ']'

    msisdn = int(msisdn)

    response = 'no response'
    if msisdn == 56999694443:
        response = build_base_message(msisdn, RSLT_ERR_PROMO_INEXISTENTE)
    elif msisdn == 56999694444:
        response = build_base_message(msisdn, RSLT_EXITO)
    elif msisdn >= 56999694448 and msisdn <= 56999694459:
        response = build_base_message(msisdn, RSLT_EXITO)
    else:
        epilogue = str(msisdn)[-2:]
        print 'epilogue[' + epilogue + ']'

        if epilogue == '14':
            response = build_base_message(msisdn, RSLT_ERR_SIN_SALDO_PP)
        elif epilogue == '10':
            response = build_base_message(msisdn, RSLT_ERR_TIPO_CLIENTE_DST)
        elif epilogue == '25':
            response = 'no response'
        else:
            print '[ERROR] not recognized msisdn[' + str(msisdn) + ']'

    return response


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

# backlog = 10, if incoming an 11th connection the request should be rejected
s.listen(10)
print 'Now socket is listening'

while 1:
    conn, addr = s.accept()  # blocking call

    print 'Connected with ' + addr[0] + ':' + str(addr[1])

    msg = conn.recv(1024)

    print 'receiving: [' + msg + ']'

    root = ET.fromstring(msg)
    req = root.find('req')
    msisdn = req.find('msisdn')

    print 'msisdn: [' + str(msisdn.text) + ']'

    response = build_response(msisdn.text)
    data = str(response)

    if not data:
        break

    if data != 'no response':
        conn.sendall(data)

conn.close()
s.close()



