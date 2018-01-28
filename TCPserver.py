# -*- coding: cp936 -*-

import socket

if __name__ == "__main__":

    print "Server is starting"
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('127.0.0.1', 25521))  # 配置socket，绑定IP地址和端口号
    sock.listen(6)  # 设置最大允许连接数，各连接和server的通信遵循FIFO原则
    print "Server is listening port 8001, with max connection 6"

    ip_portA = ('127.0.0.1', 21521)
    ip_portB = ('127.0.0.1', 22521)
    ip_portC = ('127.0.0.1', 23521)

    while True:  # 循环轮询socket状态，等待访问
        connection, address = sock.accept()

        buf = connection.recv(1024)
        print "received from client %s,%s" % (address, buf)
        buf1 = buf[0:3]
        buf2 = buf[4:]
        print "function is " + buf1
        print "the input number is " + buf2

        sk1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
        sk2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
        sk3 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)

        sk1.sendto(buf2, ip_portA)
        sk2.sendto(buf2, ip_portB)
        sk3.sendto(buf2, ip_portC)

        print "sending message is " + buf2

        bufA, addr1 = sk1.recvfrom(1024)
        sk1.sendto(bufA, ip_portA)

        bufB, addr2 = sk2.recvfrom(1024)
        sk2.sendto(bufB, ip_portB)

        bufC, addr3 = sk3.recvfrom(1024)

        print "x^2 is " + bufA
        print "x^3 is " + bufB
        print "x^5 is " + bufC

        bufA1, addr4 = sk1.recvfrom(1024)
        bufB1, addr5 = sk2.recvfrom(1024)

        print "x^4 is " + bufA1
        print "x^6 is " + bufB1

        sk1.close()
        sk2.close()
        sk3.close()

        temp1 = float(buf2)
        temp2 = float(bufA)
        temp3 = float(bufB)
        temp4 = float(bufA1)
        temp5 = float(bufC)
        temp6 = float(bufB1)

        if buf1 == "DIV":
            print "this is DIV function"
            finalValue = 1 + temp1 + temp2 + temp3 + temp4 + temp5 + temp6
        elif buf1 == "LOG":
            print "this is LOG function"
            finalValue = -1 - temp1 - temp2 / 2 - temp3 / 3 - temp4 / 4 - temp5 / 5 - temp6 / 6
        else:
            print "function error!!\n"

        Bbuf = str(finalValue)
        connection.send(Bbuf)
        print "sending back to client"  # 当一个连接监听循环退出后，连接可以关掉
        connection.close()