#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/time.h>

int clientCount = 0;


#define BUFSIZE 48000

struct client{
	int index;
	char username[1024];
	int sockID;
	struct sockaddr_in clientAddr;
	int len;

};




struct client Client[1024];

pthread_t thread[1024];


int server_buff[BUFSIZE];
void * Handler(void * attrClient){
	struct client* attrClient1 = (struct client*) attrClient;
	int index = attrClient1 -> index;
	int clientSocket = attrClient1 -> sockID;
	char username[1024];
		
	recv(clientSocket,username,1024,0);
	strcpy(Client[index].username,username);
	printf("connected\n");

	int data[BUFSIZE];
	while(1)
	{
		if(memcmp(data,server_buff,sizeof(data))){
			memcpy(data,server_buff,sizeof(data));
			printf("buffer changed\n");
			 if(send(clientSocket,data,BUFSIZE,NULL)==-1){printf("error\n");}
			 else{printf("sent");}
			}

		int read = recv(clientSocket,server_buff,BUFSIZE,0);
		if(read==-1){printf("error");}
	
	}
	return NULL;



}
	

int main(int argc,char *argv[]){

	int port;
	port = atoi(argv[1]);
	int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

//	SERVER ATTRIBUTES

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

//	BIND TO PORT

	if(bind(serverSocket,(struct sockaddr *) &serverAddr , sizeof(serverAddr)) == -1) return 0;

//	LISTEN TO INCOMING MESSAGES

	if(listen(serverSocket,1024) == -1) return 0;
	printf("INITIALIZED AT PORT %d\n",port);



	while(1){ 
		Client[clientCount].sockID = accept(serverSocket, (struct sockaddr*) &Client[clientCount].clientAddr, &Client[clientCount].len);
		Client[clientCount].index = clientCount;
		pthread_create(&thread[clientCount], NULL, Handler, (void *) &Client[clientCount]);
		clientCount ++;
	}

}
