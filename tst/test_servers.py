
import socket
import sys


class TestServers(object):

    def test_msisdn(self, cmdopt):
        print 'port[' + cmdopt + ']'
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            print 'Socket Created'

        except socket.error, msg:
            print 'Failed to create socket. Error code: ' + \
                    str(msg[0]) + \
                    ' , Error message : ' + \
                    msg[1]
            sys.exit()

        remote_ip = '127.0.0.1'
        remote_port = int(cmdopt)

        s.connect((remote_ip, remote_port))
        print 'Socket connected to ' + remote_ip + ' on ip ' + remote_ip
        expected_response = \
            '<?xml version="1.0" encoding="ISO-8859-1"?>' + \
            '<msg>' + \
            '<header action="1" id="1111"/>' + \
            '<resp>' + \
            '<op>rslt_comp_promo</op>' + \
            '<msisdn>56999694444</msisdn>' + \
            '<result>0</result>' + \
            '<strresult>OK</strresult>' + \
            '</resp>' + \
            '</msg>'

        request = '<?xml version="1.0" encoding="ISO-8859-1"?>' + \
            '<msg>' + \
            '<header action="1" id="1111"  />' + \
            '<req>' + \
            '<op>rslt_comp_promo</op>' + \
            '<msisdn>56999694444</msisdn>' + \
            '<result>0</result>' + \
            '<strresult>OK</strresult>' + \
            '</req>' + \
            '</msg>'

        try:
            s.sendall(request)
        except socket.error:
            print 'Send failed'
            sys.exit()

        print 'Message send successfully'
        # Now receive data
        reply = s.recv(4096)
        print 'message from server[' + reply + ']'

        assert expected_response == reply

        s.close()
