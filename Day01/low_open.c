#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
void error_handling(char* message);

int main(void)
{
	int fd;
	char buf[]="Let's go!\n";
	// 파일 열기
	fd=open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);
	//  파일의 오픈 모드
	// O_CREAT : 필요하면 파일을 생성
	// O_TRUNC : 기존 데이터 전부 삭제
	// O_APPEND : 기존 데이터 보존하고, 뒤에 이어서 저장
	// O_RDONLY : 읽기 전용으로 파일 오픈
	// O_WRONLY : 쓰기 전용으로 파일 오픈
	// O_RDWR : 읽기, 쓰기 겸용으로 파일 오픈
	if(fd==-1)
		error_handling("open() error!");
	printf("file descriptor: %d \n", fd);	// 파일 디스크립터 3 출력
	// 파일에 데이터 쓰기
	if(write(fd, buf, sizeof(buf))==-1)
		error_handling("write() error!");
		close(fd);	// 파일 닫기
		return  0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
