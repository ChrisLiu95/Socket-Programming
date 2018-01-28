all: 
	gcc servers.c -o servers
	gcc AWS.c -o AWS
	gcc client.c -o client

servers:
	./servers

AWS:
	./AWS

client:
	./client

.PHONY : servers AWS client
	


