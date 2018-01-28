import socket

ip_portA = ('127.0.0.1', 21521)
print "Backend server A is running..."

while True:
    sk = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
    sk.bind(ip_portA)
    data, addr = sk.recvfrom(1024)
    print data
    print addr
    temp = float(data)
    temp *= temp
    data = str(temp)
    sk.sendto(data, addr)
    print "sending x^2 to AWS:" + data

    data, addr1 = sk.recvfrom(1024)
    print data
    print addr1
    temp = float(data)
    temp *= temp
    data = str(temp)
    sk.sendto(data, addr1)
    print "sending x^4 to AWS:" + data

    sk.close()

