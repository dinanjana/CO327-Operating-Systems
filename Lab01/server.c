#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>





int main(){

int sockfd,newsockfd,n,pid;
struct sockaddr_in servaddr,cli_addr;
socklen_t clilen;
char* banner = "Hello TCP client! This is TCP server.Send the file location :\n";
char buffer[100],fileContent[20000];


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
		
		close(sockfd);

		sendto(newsockfd,banner,strlen(banner),0,(struct sockaddr*)&cli_addr,sizeof(cli_addr));
		n = recvfrom(newsockfd,buffer,1000,0,(struct sockaddr *)&cli_addr,&clilen);//information of the client by recvfrom function
		buffer[n-1] = 0;
		
	//	Reading the file

		FILE *fp;
	 
		   fp = fopen(buffer,"r"); // read mode
		   printf("The contents of %s file are :\n", buffer);
		 
		   if( fp == NULL )
		   {
		      perror("Error while opening the file.\n");
		      exit(EXIT_FAILURE);
		   }
		 
		   

		   int size = 0;

		   char ch;
		 
		   while( ( ch = fgetc(fp) ) != EOF ){
		      	printf("%c",ch);
		      	fileContent[size] = ch;
			size++;
		      
		   }
		   fclose(fp);


		sendto(newsockfd,fileContent,size+1,0,(struct sockaddr*)&cli_addr,sizeof(cli_addr));
		printf("Received:%s\n",buffer);
		exit(0);
	}
	else
	/* In parent process which continues to listen for new clients */
		close(newsockfd);
	
}
}








































































