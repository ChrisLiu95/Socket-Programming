import socket

ip_portC = ('127.0.0.1', 23521)
print('Backend server C is running...')

while True:
    sk = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
    sk.bind(ip_portC)

    data, addr = sk.recvfrom(1024)
    print data
    temp = float(data)
    temp = pow(temp, 5)
    data = str(temp)
    sk.sendto(data, addr)
    print "sending x^5 to AWS:" + data
    sk.close()

