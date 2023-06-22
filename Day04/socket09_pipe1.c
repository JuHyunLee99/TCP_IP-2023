// 프로세스간 통신 파이프(PIPE) 기법
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int fds[2];
	char str[]="Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);	//fds[0]: 파이프의 출구 즉, 데이터 수신
							//fds[1]: 파이프의 입구 즉, 데이터 전송
	pid=fork();	// 멀티프로세스
	if(pid==0)	// 자식
	{
		write(fds[1], str, sizeof(str));	// str의 문자열을 fds[1]에 저장해서 데이터 전송
	}
	else	// 부모
	{
		read(fds[0], buf, BUF_SIZE);	// 데이터 수신
		puts(buf);
	}
	return 0;
}
