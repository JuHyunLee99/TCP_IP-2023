#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char *message);
int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	char opinfo[BUF_SIZE];
  int result, opnd_cnt, i;
  int recv_cnt, recv_len;
  struct sockaddr_in serv_adr, clnt_adr;
  socklen_t clnt_adr_sz;

  if(argc!=2) {
  	printf("Usage : %s <port>\n", argv[0]);
  	exit(1);
	}

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock==-1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));	// 주소 할당
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_adr.sin_port=htons(atoi(argv[1]));

  if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
  	error_handling("bind() error");
	// 요청 수락 가능
  if(listen(serv_sock, 5)==-1)	// 5는 대기할수 있는  요청(클라이언트)의 크기
  	error_handling("listen() error");

	clnt_adr_sz=sizeof(clnt_adr);

	for(i=0; i<5; i++)
	{
		opnd_cnt=0;
		// 요청 수락, 클라이언트 소켓 생성 // for문으로 5개의 클라이언트에게 가능
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		read(clnt_sock, &opnd_cnt, 1);

		recv_len=0;
		while((opnd_cnt*OPSZ+1)>recv_len)
		{
			recv_cnt=read(clnt_sock, &opinfo[recv_len], BUF_SIZE-1);
			recv_len+=recv_cnt;
		}
		result=calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]);
		write(clnt_sock, (char*)&result, sizeof(result));

		close(clnt_sock);
	}
	// 5개의 클라이언트에게 서비스를 메공하고 나면, 마지막으로 서버 소켓을 종료
	close(serv_sock);
	return 0;
}

int calculate(int opnum, int opnds[], char op)
{
 int result=opnds[0], i;
 switch(op)
 {
 case '+':
 	for(i=1; i<opnum; i++) result+=opnds[i];
 	break;
 case '-':
 	for(i=1; i<opnum; i++) result-=opnds[i];
 	break;
 case '*':
  for(i=1; i<opnum; i++) result*=opnds[i];
  break;
 }
 return result;	
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
