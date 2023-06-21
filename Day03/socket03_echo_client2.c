#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1023
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	int str_len, recv_len, recv_cnt;
	struct sockaddr_in serv_adr;

	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	// 소켓 생성
	sock=socket(PF_INET, SOCK_STREAM, 0);	//IPv4 TCP 
	if(sock==-1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);	// 문자열을 IP 인터넷 주소로
	serv_adr.sin_port=htons(atoi(argv[2]));	// 포트
	// 연결 요청
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect() error!");

	else
		puts("Connected.......");


	while(1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if(!strcmp(message,"q\n") || !strcmp(message, "Q\n"))
			break;	// q이면 종료

		str_len=write(sock, message, strlen(message));
		// 에코 클라이언트의 해결책
		recv_len=0;
		// 클라이언트가 수신해야 할 데이터의 크기를 미리 알고 있기 때문에
		while(recv_len<str_len)	// recv_len와 str_len이 일치하는 시점전까지 반복
		{
			recv_cnt=read(sock, &message[recv_len], BUF_SIZE-1);
			if(recv_cnt==-1)
				error_handling("read() error!");
			recv_len+=recv_cnt;
		}
		message[recv_len]=0;
		printf("Message from server: %s", message);
	}
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
