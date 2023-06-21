#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;	// 서버 소켓의 파일 디스크립터 저장
	int clnt_sock;	// 클라이언트 소켓의 파일 디스크립터 저장

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[]="Hello World!";

	if(argc!=2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	// 소켓의 생성
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	// 프로토콜 체계 (Protocol Family)
	// - PF_INET: IPv4인터넷 프로토콜 체계
	// - PF_INET6: IPv6인터넷 프로토콜 체계
	// 소켓의 타입(Type): 데이터 전송 방식
	// - SOCK_STREAM: 연결지향형 소켓 TCP
	// - SOCK_DGRAM: 비 연결지향형 소켓 UDP
	
	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));	// 구조체 serv_addr 을  0으로 초기화
	serv_addr.sin_family=AF_INET;		// 주소체계(Address Family)
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); // 32bit IPv4 인터넷 주소 
	serv_addr.sin_port=htons(atoi(argv[1]));	// 16비트 TCP PORT 번호
	// 두번째 명령어(포트)를 변환해서 할당
	 
	// IP주소와 PORT번호 할당
	// serv_sock에 serv_addr에 담기  정보를 할당
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
		error_handling("bind() error");
	// 연결요청 가능상태로 변경
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	clnt_addr_size=sizeof(clnt_addr);
	//  연결요청에 대한 수락
	//  클라이어트 소켓이 만들어짐
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");

	write(clnt_sock, message, sizeof(message));
	close(clnt_sock);	// 클라이언트 소켓 닫기
	close(serv_sock);	// 서버소켓 닫기
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}		
