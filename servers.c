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

#define PortA 21521
#define PortB 22521
#define PortC 23521
#define PortAWS 24521


	int main(){
	
	struct sockaddr_in BackServer;

	int socket_descriptorA;
	int socket_descriptorB;
	int socket_descriptorC;

	socklen_t Backsize, AWSsize;
	int pid[3];
	char bufA[256];
	char bufA1[256];
	char bufB[256];
	char bufB1[256];
	char bufC[256];
	char temp[256];
        
    	pid_t fpid = fork();

	if (fpid == 0) pid[0]=getpid();
	//printf("%d\n",(int) getpid());
	if(fpid>0) {
		fpid = fork();
		if (fpid == 0) pid[1]=getpid();
	}
	if(fpid>0) {
		fpid = fork();
		if (fpid == 0) pid[2]=getpid();
	}
	if(fpid > 0){
		printf("The Server A is up and running using UDP on port %d\n", PortA );
		printf("The Server B is up and running using UDP on port %d\n", PortB );
		printf("The Server C is up and running using UDP on port %d\n", PortC );
	}
	
	BackServer.sin_family = AF_INET; /* Internet addr family */
   	BackServer.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	Backsize = sizeof(BackServer);
	

	while(1){

	if(getpid()==pid[2]){ //this is backend server A, deal with x^2

    	BackServer.sin_port = htons(PortA); // 
   
   	socket_descriptorA = socket(AF_INET,SOCK_DGRAM,0); 

	if(bind(socket_descriptorA,(struct sockaddr *)&BackServer,sizeof(BackServer))==-1){
		printf("bind error!");	
	}
	
	if(recvfrom(socket_descriptorA,bufA,sizeof(bufA),0,(struct sockaddr *)&BackServer,&Backsize)==-1){
		printf("Received error! (A)");	
	}   
	printf("Server A: Received input<%s>\n",bufA); 

	double ftemp1 = atof(bufA);
	ftemp1 *= ftemp1;
	sprintf(temp,"%f",ftemp1);
	strcpy(bufA,temp);
	//printf("x^2 is :%s\n",bufA);
	bzero(temp,sizeof(temp));  
	
	printf("The Server A calculated square <%s>\n",bufA);

	if(sendto(socket_descriptorA,bufA,sizeof(bufA),0,(struct sockaddr *)&BackServer,Backsize)==-1){
		printf("sending back to AWS error!");
	}
	
	printf("The Server A finished sending the output to AWS\n");
	
	if(recvfrom(socket_descriptorA,bufA1,sizeof(bufA1),0,(struct sockaddr *)&BackServer,&Backsize)==-1){
		printf("received error!");
	} 
	//printf("Server A: Received x^2 from server:%s\n",bufA1);
	
	printf("Server A: Received input<%s>\n",bufA1); 
	
	float ftemp4 = atof(bufA1);
	ftemp4 *= ftemp4;
	sprintf(temp,"%f",ftemp4);
	strcpy(bufA1,temp);
	//printf("x^4 is :%s\n",bufA1);
	bzero(temp,sizeof(temp));  

	printf("The Server A calculated square <%s>\n",bufA1);

	if(sendto(socket_descriptorA,bufA1,sizeof(bufA1),0,(struct sockaddr *)&BackServer,Backsize)==-1){
		printf("sending back to AWS error!");
	}

	printf("The Server A finished sending the output to AWS\n");
	
	close(socket_descriptorA);
 
	}

	sleep(1);

	if(getpid()==pid[1]){  //this is backend server B, deal with x^3

	BackServer.sin_port = htons(PortB);   	
   	socket_descriptorB = socket(AF_INET,SOCK_DGRAM,0);
	bind(socket_descriptorB,(struct sockaddr *)&BackServer,sizeof(BackServer)); 
	recvfrom(socket_descriptorB,bufB,sizeof(bufB),0,(struct sockaddr *)&BackServer,&Backsize); 
  
	printf("Server B Received input <%s>\n",bufB); 

	bzero(temp,sizeof(temp));

	float ftemp2 = atof(bufB);
	ftemp2 = ftemp2*ftemp2*ftemp2;
	sprintf(temp,"%f",ftemp2);
	strcpy(bufB,temp);
	//printf("x^3 is :%s\n",bufB); 
	bzero(temp,sizeof(temp));  
	
	printf("The Server B calculated cube <%s>\n",bufB);
	
 	sendto(socket_descriptorB,bufB,sizeof(bufB),0,(struct sockaddr *)&BackServer,Backsize);  

	printf("The Server B finished sending the output to AWS\n");
	
	recvfrom(socket_descriptorB,bufB1,sizeof(bufB1),0,(struct sockaddr *)&BackServer,&Backsize); 
	printf("Server B: Received input <%s>\n",bufB1);

	float ftemp5 = atof(bufB1);
	ftemp5 = ftemp5*ftemp5;
	sprintf(temp,"%f",ftemp5);
	strcpy(bufB1,temp);
	//printf("x^6 is :%s\n",bufB1);
	bzero(temp,sizeof(temp));  

	printf("The Server B calculated cube <%s>\n",bufB1); 

	sendto(socket_descriptorB,bufB1,sizeof(bufB1),0,(struct sockaddr *)&BackServer,Backsize);  
	
	printf("The Server B finished sending the output to AWS\n");
	close(socket_descriptorB);
	}
	
	sleep(1);

	if(getpid()==pid[0]){ 	//this is backend server C, deal with x^5
		
    	BackServer.sin_port = htons(PortC); // ?
   	socket_descriptorC = socket(AF_INET,SOCK_DGRAM,0);   // UDP socket
	bind(socket_descriptorC,(struct sockaddr *)&BackServer,sizeof(BackServer)); 
	recvfrom(socket_descriptorC,bufC,sizeof(bufC),0,(struct sockaddr *)&BackServer,&Backsize);  
	printf("Server C Received input <%s>\n",bufC); 
	
	float ftemp3 = atof(bufC);

	ftemp3 = ftemp3*ftemp3*ftemp3*ftemp3*ftemp3;
	sprintf(temp,"%f",ftemp3);
	strcpy(bufC,temp);
	//printf("x^5 is:%s\n",bufC); 
	bzero(temp,sizeof(temp));  

	printf("The Server C calculated 5th power <%s>\n",bufC);
	

	/*******send x^5 to AWS*******/
	sendto(socket_descriptorC,bufC,sizeof(bufC),0,(struct sockaddr *)&BackServer,Backsize);  

	printf("The Server C finished sending the output to AWS\n");
	

	close(socket_descriptorC);
	
		}
 	}
return 0;
}
