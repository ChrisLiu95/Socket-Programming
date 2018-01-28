import socket

if __name__ == "__main__":

    while True:

        flag = raw_input("Please input the function and number:")
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect(('127.0.0.1', 25521))
        sock.send(flag)

        data = sock.recv(1024)
        print "the received value is  " + data
        sock.close()
