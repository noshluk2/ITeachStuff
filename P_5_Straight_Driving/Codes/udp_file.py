import socket

UDP_IP = "192.168.43.20"
UDP_PORT = 9999
MESSAGE = "10,650,800"

#print "UDP target IP:", UDP_IP
#print "UDP target port:", UDP_PORT
#print "message:", MESSAGE

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.sendto(bytes(MESSAGE.encode('utf-8')), (UDP_IP, UDP_PORT))
