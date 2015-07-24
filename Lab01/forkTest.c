#include<stdlib.h>
#include<stdio.h>
int main(void)
{
int pid;
pid = fork();
	

	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}else if(pid > 0 ){
		
		wait();	
	
	}
	if (pid == 0)
		puts("This is the child process");
	else
		puts("This is the parent process");

return 0;

}
