import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

S = input('S=')
while True:
    res = s.sendto(S.encode(), ("10.131.6.146", 1234))

s.close()

