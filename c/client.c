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

int main(int argc, char *argv[]){  //input number and function

	printf("The client is up and running.\n");
    	printf("The client sent <%s> and <%s> to the AWS.\n",argv[1],argv[2]);
	
	char *sendParameter;
        char awsResponse[256];
	char buff[256];
	float value;

	sendParameter=(char*)malloc(sizeof(char)*256);
    	memset(sendParameter,'\0',sizeof(char)*256);

	if(argc!=3){

    	printf("Format error! Please enter: ./client <function> <input>\n"); // format error
    		exit(1);
    			}else if(strlen(argv[1])!=3){
    				printf("Function error! Please enter: ./client <function(DIV or LOG)> <input>\n"); // format error
    			exit(1);
    				} else {
    					strcat(sendParameter,argv[1]);
					strcat(sendParameter," ");
    					strcat(sendParameter,argv[2]);
					strcat(sendParameter," ");
    }

 	struct sockaddr_in ClntAddr; //client socket
	int client_socket;
	client_socket = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in ServAddr; // AWS socket
  
   	ServAddr.sin_family = AF_INET; /* Internet addr family */
    	ServAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //inet_addr("127.0.0.1");
    	ServAddr.sin_port = htons(25521); //server port
    	socklen_t ServSize = sizeof(ServAddr);

	int connect_socket = connect (client_socket, (struct sockaddr*) &ServAddr, sizeof(ServAddr)); //connect to the AWS
	/***********get client Ip address and dynamic Portnumber************/
	int getsock_check=getsockname(client_socket,(struct sockaddr *)&ServAddr, &ServSize);
	//Error   checking
	if(getsock_check== -1) {
	perror("getsockname");
	exit(1);
	 }
	else{
		//printf("current IP address is %s\n",inet_ntoa(ServAddr.sin_addr));
		//printf("current port number is %d\n", ntohs(ServAddr.sin_port));
		int d= ntohs(ServAddr.sin_port); //port number
		//printf("d is %d\n",d);
		sprintf(buff,"%d",d);
		strcat(sendParameter,buff);
		bzero(buff, sizeof(buff));
	}

   	if (connect_socket == -1) {
    		printf ("connect error!!\n");
   				 }
	printf("Sending message %s to server \n",sendParameter);

    	if(send(client_socket, sendParameter, strlen(sendParameter),0)==-1){
    		printf("Sending error\n");
    		exit(1);
  	  }
 
	
	bzero(awsResponse, sizeof(awsResponse));	
	recv(client_socket, awsResponse, sizeof(awsResponse),0);

	/*value=atof(awsResponse);

	printf("return value is : %s\n",awsResponse);

	printf("return value is : %f\n",value); */

   	printf("According to AWS < %s > on < %s > : < %s > \n",argv[1],argv[2],awsResponse);



    	close(client_socket);
	
return 0;
}
