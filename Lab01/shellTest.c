//Simple shell
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	int pid;
	char arg1[200];
	char arg2[200];
	while(1){
	
		pid = fork();
		wait();

		if(pid < 0){
			puts("fork error");
		}
		
		if(pid == 0){
			
			puts("\nEnter a command:") ;
			gets(arg1);
			puts("\nEnter the path:") ;
			gets(arg2);
			
			execl(arg1, "-l",arg2, NULL);
		}
		//execl(arg);
		
	}
}
