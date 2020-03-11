import socket
import struct
from contextlib import closing

class UDPReceiver:
	def __init__(self, ip, port):
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.sock.bind((ip, port))

	def receive(self):
		msg, address = self.sock.recvfrom(1024)
		msg_decoded = msg.decode('utf-8')
		return msg_decoded, address
