
class NetworkConfig:
    def __init__(self):
        self.IP = '127.0.0.1'
        self.PORT = 4040

    def connection_data(self):
        return (self.IP, self.PORT)
