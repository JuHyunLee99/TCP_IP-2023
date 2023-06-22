// 좀비 프로세스의 소멸2: waitpid 함수
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid=fork();

	if(pid==0)
	{
		sleep(15);
		return 24;
	}
	else 
	{
		while(!waitpid(-1, &status, WNOHANG))	// wait함수의 브로킹 문제 해결
		{
			sleep(3);
			puts("sleep 3sec.");
		}
		
		if(WIFEXITED(status))
			printf("Child send one: %d \n", WEXITSTATUS(status));
	}
	return 0;
}
