#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int i;
	struct hostent *host;	// 도메인의 IP주소정보들의 구조체
	if(argc!=2) {
		printf("Usage : %s <addr>=n", argv[0]);
		exit(1);
	}
	
// 도메인 이름으로부터 IP의 주소정보를 얻는 함수 
	host=gethostbyname(argv[1]);	// 성공시 hostent 구조체 변수의 주소값, 실패시 NULL
	if(!host)	// 실패시
		error_handling("gethost... error");

	printf("official name: %s \n", host->h_name);	// 공식 도메인 이름
	for(i=0; host->h_aliases[i]; i++)
		printf("Aliases %d: %s \n", i+1, host->h_aliases[i]);	// 공식 도메인 이름 외에에 접속할 수 있는 다른 도메인이름
	printf("Address type: %s \n",
			(host->h_addrtype==AF_INET)?"AF_INET":"AF_INET6");	// IP 주소체계
	for(i=0; host->h_addr_list[i]; i++)		// 도메인 이름에 대한 정수 형태의 IP주소들의 리스트
		printf("IP addr %d: %s \n", i+1,
			inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));	// 형변환함. why?
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

