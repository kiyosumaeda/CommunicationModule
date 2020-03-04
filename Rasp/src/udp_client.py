import threading
import time
from socket import *

class ServerThread(threading.Thread):
    def __init__(self, port):
        threading.Thread.__init__(self)
        self.data = 'hoge'
        self.kill_flag = False
        # line information
        self.HOST = gethostname()
        self.port = port
        self.BUFSIZE = 1024
        self.ADDR = (gethostbyname(self.HOST), self.port)
        # bind
        self.udpServSock = socket(AF_INET, SOCK_DGRAM)
        self.udpServSock.bind(self.ADDR) # HOST, PORTでbinding

    def run(self):
        while True:
            try:
                data, self.addr = self.udpServSock.recvfrom(self.BUFSIZE) # データ受信
                self.data = data.decode()
            except:
                pass

if __name__ == '__main__':
    th = ServerThread()
    th.setDaemon(True)
    th.start()

    while True:
        if not th.data:
            break
        print(th.data)
        time.sleep(0.1)
