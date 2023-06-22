// 좀비 프로세스
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid=fork();
	// 부모 프로세스 : fork 함수의 반환 값은 자식 프로세스의 ID
	// 자식 프로세스 : fork 함수의 반환 값은 0

	if(pid==0) // if Child Process
	{
		puts("Hi I am a child process");
	}
	else
	{
		printf("Child Process ID: %d \n", pid);
		sleep(30);	// Sleep 30 sec.	// 자식프로세스 좀비확인을 위해 부모 프로세스의 종료 지연
	}

	if(pid==0)
		puts("End child process");
	else
		puts("End parent process");
	return 0;
}
