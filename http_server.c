#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <sys/sendfile.h>
#include <stdlib.h>
#include <unistd.h>

#define PORTNO 8085

int main(int argc, char *argv[])
{
	int  sockfd,clientfd;
	struct sockaddr_in server,client;
	int mysock;
	char buffer[2048];
	/*char servmsg[2024] = "HTTP/1.1 200 OK\n"
"Date: Mon, 27 Jul 2009 12:28:53 GMT\n"
"Server: Apache/2.2.14 (Win32)\n"
"Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n"
"Content-Length: 88\n"
"Content-Type: text/html\n"
"Connection: Closed\n\n"
"<html>"
"<body>"
"<h1><center>Hello, Kartiki!</center></h1>"
"</body>"
"</html>";*/
	int b;
	
	sockfd =  socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)	printf("Error creating socket");
	//printf("\nPORT NO set to 9090");	
	server.sin_port = htons(PORTNO);

	server.sin_family = AF_INET;
	//server.sin_addr.s_addr = inet_addr("192.168.89.128"); 
	server.sin_addr.s_addr = INADDR_ANY; 
	//printf("\nConfigured the IP Address");

	b = bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	printf("\nTCP Server is Online\n");
	if(b < 0)	perror("Binding Failed");
	listen(sockfd,1);	
	clientfd = accept(sockfd,(struct sockaddr *)&client,&clientfd);
	printf("Received Client Connection\n\n");
	read(clientfd,buffer,2048);
	printf("%s",buffer);
    int index = open("index.html",O_RDONLY);
 //   int image = open("chip.jpg",O_RDONLY);
//	sendfile(clientfd,image,NULL,4000);
	sendfile(clientfd,index,NULL,4000);
    close(index);
    close(clientfd);
 //   close(image);
	
	return 0;
	
}
