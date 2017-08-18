
class NetworkConfig:
    def __init__(self, ip, port):
        self.IP = str(ip)
        self.PORT = int(port)

    def connection_data(self):
        return (self.IP, self.PORT)
