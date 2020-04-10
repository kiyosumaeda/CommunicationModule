import socket

class UDPSender:
	def __init__(self, ip, port):
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.ip = ip
		self.port = port

	def send(self, msg):
		self.sock.sendto(msg.encode(), (self.ip, self.port))

	def close(self):
		self.sock.close()
