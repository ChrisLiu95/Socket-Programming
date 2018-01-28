import socket

ip_portB = ('127.0.0.1', 22521)

print "Backend server B is running..."

while True:
    sk = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
    sk.bind(ip_portB)
    data, addr = sk.recvfrom(1024)
    print data
    print addr
    temp = float(data)
    temp = pow(temp, 3)
    data = str(temp)
    print data
    sk.sendto(data, addr)
    print "sending x^3 to AWS:" + data

    data, addr1 = sk.recvfrom(1024)
    print data
    print addr1
    temp = float(data)
    temp = pow(temp, 2)
    data = str(temp)
    sk.sendto(data, addr1)
    print "sending x^6 to AWS:" + data
    sk.close()
