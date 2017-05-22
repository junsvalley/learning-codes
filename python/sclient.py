#!/usr/bin/python
import socket
import struct
import time
import random
import threading
HOST='127.0.0.1'
PORT=2016

class tlv:
	def __init__(self):
		self.vtype = 0
		self.length = 0
		self.value = ""
	def ToBuffer(self):
		fmt = "!II%ds" % self.length
		#fmt = "II%ds" % self.length
		packer = struct.Struct(fmt)
		buf = packer.pack(self.vtype, self.length, self.value)
		return buf


s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((HOST,PORT))
s.setblocking(1)

def send_msg(abc):
	loopcnt = 1
	while loopcnt <= 100:
		tlvInst = tlv()
		tlvInst.vtype=1#int(raw_input("Please input type:"))
		tlvInst.value="x" * random.randint(1024, 10240)#raw_input("Please input value:")
		tlvInst.length=len(tlvInst.value)
		print "send loop cnt %d, vlen %d" %(loopcnt, tlvInst.length)#repr(tlvInst.ToBuffer())
		s.sendall(tlvInst.ToBuffer())
		loopcnt += 1
		#time.sleep(0.001)
	
def recv_msg(abc):
	loopcnt = 1
	while 1:
		data = s.recv(4)
		vtype = struct.unpack("!I", data)
		data = s.recv(4)
		length = struct.unpack("!I", data)
		data = s.recv(length[0])
		print "[%d] %d, type %d" %(loopcnt, length[0], vtype[0])
		loopcnt += 1

def main():
		thread_list = list()
		thread_name = "thread_send"
		thread_list.append(threading.Thread(target = send_msg, name = thread_name, args = (None,)))
		thread_name = "thread_recv"
		thread_list.append(threading.Thread(target = recv_msg, name = thread_name, args = (None,)))

		for thread in thread_list:
				thread.start()

		for thread in thread_list:
				thread.join()

if __name__ == "__main__":
	main()

s.close()
