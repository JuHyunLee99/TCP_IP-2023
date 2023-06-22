// 멀티프로세스 기반 서버의 구현 fork()
#include <stdio.h>
#include <unistd.h>

int gval=10;
int main(int argc, char *argv[])
{
	pid_t pid;	// 자식 프로세스 ID
	int lval=20;
	gval++, lval+=5;

	pid=fork();	// 호출한 프로세스의 복사본 생성
	// 부모프로세스: fork함수의 반환 값은 자식 프로세스의 ID
	// 자식프로세스: fork함수의 반환 값은 0
	if(pid==0)	//if Chlid Process
		gval+=2, lval+=2;
	else				//if Parent Process
		gval-=2, lval-=2;

	if(pid==0)
		printf("Child Proc: [%d, %d] \n", gval, lval);
	else
		printf("Parent Proc: [%d, %d] \n", gval, lval);
	return 0;
}
