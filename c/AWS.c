#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <sys/wait.h>
char *host_name ="127.0.0.1";

int main(int argc, char **argv){
	
	char *temp1,*temp2,*temp3,*token;
	char s[2] = " ";
	char buf[256];
	char bufA[256];
	char bufA2[256];
	char bufA3[256];
	char bufB[256];
	char bufB2[256];
	char bufB3[256];
	char bufC[256];
	char temp[256];
	char awsresponse [256];
	socklen_t Clntsize;
	socklen_t Servsize,sizeA,sizeB,sizeC;
	int client_socket,fd1;
	
	bzero(awsresponse, sizeof(awsresponse));

	
	float ftemp1,ftemp2,ftemp3,ftemp4,ftemp5,ftemp6,finalValue;
	
	struct sockaddr_in BackAddrA; // backend Server A
	struct sockaddr_in BackAddrB; // backend Server B
	struct sockaddr_in BackAddrC; // backend Server C
	struct sockaddr_in ClntAddr; // client socket
	struct sockaddr_in ServAddr; // AWS socket /TCP
	struct sockaddr_in UDPserver; 

	int aws_socket;
	int udp_socketA;
	int udp_socketB;
	int udp_socketC;

	printf("The AWS is up and running, waiting for connection....\n");

	bzero(&ServAddr, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET; /* Internet addr family */
   	ServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //inet_addr("192.168.140.1");
   	ServAddr.sin_port = htons(25521); //server port
	Servsize = sizeof(ServAddr);

	bzero(&BackAddrA, sizeof(BackAddrA));
	BackAddrA.sin_family = AF_INET; /* Internet addr family */
   	BackAddrA.sin_addr.s_addr = inet_addr("127.0.0.1");  //inet_addr("192.168.140.1");
   	BackAddrA.sin_port = htons(21521); 
	sizeA = sizeof(BackAddrA);

	bzero(&BackAddrB, sizeof(BackAddrB));
	BackAddrB.sin_family = AF_INET; /* Internet addr family */
   	BackAddrB.sin_addr.s_addr = INADDR_ANY;  //inet_addr("192.168.140.1");
   	BackAddrB.sin_port = htons(22521); 
	sizeB = sizeof(BackAddrB);

	bzero(&BackAddrC, sizeof(BackAddrC));
	BackAddrC.sin_family = AF_INET; /* Internet addr family */
   	BackAddrC.sin_addr.s_addr = inet_addr("127.0.0.1"); //inet_addr("192.168.140.1");
   	BackAddrC.sin_port = htons(23521);
	sizeC = sizeof(BackAddrC);
	
	/*bzero(&UDPserver, sizeof(UDPserver));
	BackAddrC.sin_family = AF_INET; /* Internet addr family 
   	BackAddrC.sin_addr.s_addr = inet_addr("127.0.0.1"); //inet_addr("192.168.140.1");
   	BackAddrC.sin_port = htons(24521);
	sizeU = sizeof(UDPserver);*/
 
	aws_socket = socket(AF_INET,SOCK_STREAM,0); //aws socket, over TCP
	
	fd1 = socket(AF_INET, SOCK_STREAM, 0);
	fd1 = bind(aws_socket, (struct sockaddr *)&ServAddr, Servsize);

    	if(fd1==-1){
    	perror("Bind error");
    } //bind 

   	if(listen(aws_socket, 6)==-1){
    	perror("Listen error");
    } //listen the request from client, up to 6

while(1){
	//printf("lalala\n");
	Clntsize = sizeof(ClntAddr);
   	client_socket = accept(aws_socket, (struct sockaddr *)&ClntAddr,&Clntsize); //accept the connection

    	if(client_socket==-1){
    		perror("Accept error");
    }

	if(recv(client_socket,buf,sizeof(buf),0)==-1){   //recieve the number and function from client
    		perror("Recieve error");
    	}else{  

		token = strtok(buf, s);
   		temp1 = token;	
		//printf( "temp1 is :%s\n", temp1 ); //function

      		token = strtok(NULL, s);
		temp2 = token;
		//printf( "temp2 is :%s\n", temp2 ); //number
	
		token = strtok(NULL, s);
		temp3 = token;
		//printf( "temp3 is :%s\n", temp3 ); // Port number	
  		
    	}

   	printf("The AWS received input %s and function = %s from the client using TCP over port 21521\n", temp2, temp1);

	udp_socketA = socket(AF_INET,SOCK_DGRAM,0); 
	bind(udp_socketA,(struct sockaddr *)&BackAddrA,sizeA); 

	udp_socketB = socket(AF_INET,SOCK_DGRAM,0); //udp socket to B
	bind(udp_socketB,(struct sockaddr *)&BackAddrB,sizeB);

	udp_socketC = socket(AF_INET,SOCK_DGRAM,0); //udp socket to C
	bind(udp_socketC,(struct sockaddr *)&BackAddrC,sizeC);
	
	/*******************Set up UDP connection to backend Server A,B,C********/
	if(sendto(udp_socketA,temp2,sizeof(temp2),0,(struct sockaddr *)&BackAddrA,sizeof(BackAddrA))==-1){
    		perror("udp_socket sending error");
    }  
	printf( "The AWS sent < %s > to Backend-ServerA\n", temp2);
	//printf("current port number is %d\n", ntohs(BackAddrA.sin_port));

	if(sendto(udp_socketB,temp2,sizeof(temp2),0,(struct sockaddr *)&BackAddrB,sizeof(BackAddrB))==-1){
    		perror("udp_socket sending error");
    }	
	printf( "The AWS sent < %s > to Backend-ServerB\n", temp2);
	
	if(sendto(udp_socketC,temp2,sizeof(temp2),0,(struct sockaddr *)&BackAddrC,sizeof(BackAddrC))==-1){
    		perror("udp_socket sending error");
    } 
	printf( "The AWS sent < %s > to Backend-ServerC\n", temp2);
 
	/**********reveive the response value by the Backend Server A,B,C through UDP*****/

	bzero(bufA, sizeof(bufA));
	bzero(bufB, sizeof(bufB));
	bzero(bufC, sizeof(bufC));
	bzero(bufA2, sizeof(bufA2));
	bzero(bufB2, sizeof(bufB2));

        /*************x^2 and x^4*****************/
	if(recvfrom(udp_socketA,bufA,sizeof(bufA),0,(struct sockaddr *)&BackAddrA,&sizeA)==-1){
		perror("udp_socketA receiving error");	
	}   
	printf("The AWS received < %s >  Backend-Server<A> using UDP over port <24521>\n",bufA);
	
	strcpy(bufA2,bufA);
	
	if(sendto(udp_socketA,bufA2,sizeof(bufA2),0,(struct sockaddr *)&BackAddrA,sizeof(BackAddrA))==-1){
    		perror("udp_socket sending error");
    }  

	printf("The AWS sent < %s > to Backend-Server A\n",bufA2);
			
	if(recvfrom(udp_socketA,bufA3,sizeof(bufA3),0,(struct sockaddr *)&BackAddrA,&sizeA)==-1){
		perror("udp_socketB receiving error");	
	}   
     	
	printf("The AWS received < %s >  Backend-Server<A> using UDP over port <24521>\n",bufA3);

        /*************x^3 and x^6*****************/
	if(recvfrom(udp_socketB,bufB,sizeof(bufB),0,(struct sockaddr *)&BackAddrB,&sizeB)==-1){
		perror("udp_socketB receiving error");	
	}   

	printf("The AWS received < %s >  Backend-Server<B> using UDP over port <24521>\n",bufB);
	strcpy(bufB2,bufB);

	if(sendto(udp_socketB,bufB2,sizeof(bufB2),0,(struct sockaddr *)&BackAddrB,sizeof(BackAddrB))==-1){
    		perror("udp_socket sending error");
	}

	printf("The AWS sent < %s > to Backend-Server B\n",bufA);

	if(recvfrom(udp_socketB,bufB3,sizeof(bufB3),0,(struct sockaddr *)&BackAddrB,&sizeB)==-1){
		perror("udp_socketB receiving error");	
	}   
     	
	printf("The AWS received < %s >  Backend-Server<B> using UDP over port <24521>\n",bufB3);

	/****************x^5*************************/
	if(recvfrom(udp_socketC,bufC,sizeof(bufC),0,(struct sockaddr *)&BackAddrC,&sizeC)==-1){
		perror("udp_socketc receiving error");
	}  
	printf("The AWS received < %s >  Backend-Server<C> using UDP over port <24521>\n",bufC);

	close(udp_socketA); 
	close(udp_socketB); 
	close(udp_socketC); 

 	ftemp1 = atof(temp2); //x
	ftemp2 = atof(bufA); //x^2
	ftemp3 = atof(bufB); //x^3
	ftemp4 = atof(bufA3); //x^4
	ftemp5 = atof(bufC); //x^5
	ftemp6 = atof(bufB3); //x^6
	
	printf("Values of powers received by AWS: < %f %f %f %f %f %f > \n",ftemp1,ftemp2,ftemp3,ftemp4,ftemp5,ftemp6);

	/*******************send back the value to the client**/
	if(strcmp(temp1,"DIV")==0){   //funtion DIV

		finalValue= 1 + ftemp1 + ftemp2 + ftemp3 + ftemp4 + ftemp5 + ftemp6;
	
		printf("AWS calculated DIV on < %s >: < %f >\n", temp2, finalValue);

		sprintf(temp,"%f",finalValue);
		strcat(awsresponse,temp);
		bzero(temp,sizeof(temp));

	} else if(strcmp(temp1,"LOG")==0){   //function LOG
		//printf("this is the LOG function!\n");
	
		finalValue=  - ftemp1 - ftemp2/2 - ftemp3/3 - ftemp4/4 - ftemp5/5 - ftemp6/6;
	
		printf("AWS calculated LOG on < %s >: < %f >\n", temp2, finalValue);
	
		bzero(awsresponse, sizeof(awsresponse));

		sprintf(temp,"%f",finalValue);
		strcat(awsresponse,temp);
		bzero(temp,sizeof(temp));
	
		}else{  printf("error!!\n");
	}

	send(client_socket, awsresponse, sizeof(awsresponse), 0);
	bzero(awsresponse, sizeof(awsresponse));

	printf("AWS sent < %f > to client\n", finalValue);
	
	close(client_socket);    
	}		
  
	close(aws_socket); 	 
	
return 0;
}
