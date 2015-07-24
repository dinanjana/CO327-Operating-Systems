#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




int main(){

int sockfd,newsockfd,n,pid,listenfd;
struct sockaddr_in servaddr,cli_addr;
socklen_t clilen;
char* banner = "Hello TCP client! This is TCP server";
char buffer[100];
//char banner1[1000],ch;
//char file_name [25] ; //"TCPClient.c";
//char file_size[] = "10000";

/* one socket is dedicated to listening */
sockfd=socket(AF_INET,SOCK_STREAM,0);
	
/* initialize a sockaddr_in struct with our own address information for
binding the socket */
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(12345);

/* binding */
bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
listen(sockfd,5);
clilen = sizeof(cli_addr);

while (1)
{
/* New socket descriptor is returned each time a client connects*/
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
if (newsockfd < 0)
{
	perror("ERROR on accept");
	exit(1);
}
pid = fork();
if (pid < 0)
{
	perror("ERROR on fork");
	exit(1);
}
if (pid == 0)
{
/* In child process which the handles client connection */
	//connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen); // the uninitialized cliaddr variable is filled in with the
	
	
	close(sockfd);
//	handle_client(newsockfd);
	n = recvfrom(newsockfd,buffer,1000,0,(struct sockaddr *)&cli_addr,&clilen);//information of the client by recvfrom function
	buffer[n] = 0;
	sendto(newsockfd,banner,strlen(banner),0,(struct sockaddr*)&cli_addr,sizeof(cli_addr));
	printf("Received:%s\n",buffer);
	exit(0);
}
else
/* In parent process which continues to listen for new clients */
	close(newsockfd);
}
}
