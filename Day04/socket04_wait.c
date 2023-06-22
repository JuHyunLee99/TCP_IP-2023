// 좀비 프로세스의 소멸1: wait 함수의 사용
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid=fork();	// fork

	if(pid==0)
	{
		return 3;	//자식 프로세스 종료
	}
	else 
	{
		printf("Child PID: %d \n", pid);
		pid=fork();	// fork
		if(pid==0)
		{
			exit(7);	// 자식 포로세스 종료
		}
		else
		{
			printf("Child PID: %d \n", pid);
			wait(&status);		
			// wait(): 자식 프로세스가 종료되면서 전달한 값이 매개변수로 전달된 주소의 변수에 저장됨.
			// 주의점: wait함수 호출된 시점에서 종료된 자식 프로세스가 없다면, 임의의 자식 프로세스가 종료될 때까지 브로킹 상태
			if(WIFEXITED(status))	// WIFEXITED: 자식 프로세스가 정상 종료한 경우 참(True) 반환
				printf("Child send one: %d \n", WEXITSTATUS(status));	// WEXITSTATUS: 자식 프로세스의 전달 값을 반환

			wait(&status);
			if(WIFEXITED(status))
				printf("Child send two: %d \n", WEXITSTATUS(status));
			sleep(30);
		}
	}
	return 0;
}
