a. Name: XIANGCHONG LIU
b. USC ID: 2267103521
c. What   I   have   done   in   the  assignment
In this socket programming project, I built a AWS network based on TCP and UDP. What I have done containing the establishment the TCP connection between client to AWS server, and the UDP connection between AWS server and backend server, so that we can get the output from the server side if there's a input from client. Meanwhile, fork() function is used to create multiple back-end server at the same time. I learned how to write socket programming program in C, and I even wrote a different version in Python! Also, I learned how to write makefile and the readme file.
d. What your code files are and what each one of them does. 

client.c: This file allows client inputting a function(DIV/LOG) and a number, then a TCP connection between client and AWS server will be established. Through this connection, the input function and number will be sent to the AWS, and AWS will deal with these data and return a final estimate value back to the client.

AWS.c: This file represents the AWS server. It will receive the input of client via TCP connection, and send the input value to the backend server A,B,C via UDP connection. After receiving the return value from the back-end server, which are used for dealing some calculation, it will calculate the estimate value based on the function and return value from the back-end server, then it will send the final value to the client.

servers.c: This file creates Server A,B,C by using fork() function, different code are applied in different child process. Server A can calculate x^2, Server B can calculate x^3, and Server C can calculate x^5. Back-end servers will return the calculated values after they receiving the input value of AWS.

e. The   format   of   all   the   messages   exchanged.
client.c:
The client is up and running.
The client sent <LOG> and <0.5> to the AWS.
Sending message LOG 0.5 50242 to server 
According to AWS < LOG > on < 0.5 > : < -0.691146 > 

AWS.c:
The AWS is up and running, waiting for connection....
The AWS received input 0.5 and function = LOG from the client using TCP over port 21521
The AWS sent < 0.5 > to Backend-ServerA
The AWS sent < 0.5 > to Backend-ServerB
The AWS sent < 0.5 > to Backend-ServerC
The AWS received < 0.250000 >  Backend-Server<A> using UDP over port <24521>
The AWS sent < 0.250000 > to Backend-Server A
The AWS received < 0.062500 >  Backend-Server<A> using UDP over port <24521>
The AWS received < 0.125000 >  Backend-Server<B> using UDP over port <24521>
The AWS sent < 0.250000 > to Backend-Server B
The AWS received < 0.015625 >  Backend-Server<B> using UDP over port <24521>
The AWS received < 0.031250 >  Backend-Server<C> using UDP over port <24521>
Values of powers received by AWS: < 0.500000 0.250000 0.125000 0.062500 0.031250 0.015625 > 
AWS calculated LOG on < 0.5 >: < -0.691146 >
AWS sent < -0.691146 > to client

servers.c:
The Server A is up and running using UDP on port 21521
The Server B is up and running using UDP on port 22521
The Server C is up and running using UDP on port 23521
Server A: Received input<0.5>
The Server A calculated square <0.250000>
The Server A finished sending the output to AWS
Server B Received input <0.5>
The Server B calculated cube <0.125000>
The Server B finished sending the output to AWS
Server C Received input <0.5>
The Server C calculated 5th power <0.031250>
The Server C finished sending the output to AWS
Server A: Received input<0.250000>
The Server A calculated square <0.062500>
The Server A finished sending the output to AWS
Server B: Received input <0.125000>
The Server B calculated cube <0.015625>
The Server B finished sending the output to AWS

g. Any idiosyncrasy of your project. It should say under what conditions the
project fails, if any.

As long as you run my code correctly, I can't find the failure situation. 
The correct format of running client.c should be:
./client DIV(or LOG) 0.4, the function name DIV and LOG should be capital. There will be error detection if you input the wrong function name as well.


h. Reused Code: Did you use code from anywhere for your project? If not, say
so. If so, say what functions and where they're from. 

I learned key concepts from some technical blogs and youtube and write the code down totally by myself.