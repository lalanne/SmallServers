
import xml.etree.ElementTree as ET

class Parser:
    def __init__(self, msg):
        self.msg = msg

    def msisdn(self):
        root = ET.fromstring(self.msg)
        req = root.find('req')
        msisdn = req.find('msisdn')

        return msisdn
