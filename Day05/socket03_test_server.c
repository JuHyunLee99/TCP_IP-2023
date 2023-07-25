#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#define BUF_SIZE 2048
#define IMG_BUF_SIZE  100000
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;	// 서버소켓, 클라이언트 소켓
	char buf[BUF_SIZE];	// 버프
	//HTML 문자열
	char webpage[]="HTTP/1.1 200 OK\r\n"
							"Server:Linux Web Server\r\n"
							"Content-Type: text/html; charset=UTF-8\r\n\r\n"
							"<!DOCTYPE html>\r\n"
							"<html><head><title> My Web Page </title> \r\n"
							"<style>body {background-color: #FFFF00;}</style></head>\r\n"
							"<body><center><h1>Hello world!!</h1><br>\r\n"
							"<img src=\"game.jpg\"></center></body></html>\r\n";																			
  struct sockaddr_in serv_adr, clnt_adr;	// 서버소켓 주소, 클라이언트 소켓 주소
  socklen_t clnt_adr_sz;	// 클라이언트 주소 크기

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
	while(1)
	{
		// 요청 수락, 클라이언트 소켓 생성
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		if(clnt_sock==-1)
			error_handling("accept() error");
		else
			printf("Connected client \n");
		// 읽어오자
		if(read(clnt_sock, buf, BUF_SIZE)==-1)
			printf("read 오류남");
		else
		{
			printf("%s", buf);
			if(strstr(buf,"game.jpg")!= NULL)	// 사진 요청이면
			{
				int fdimg=open("game.jpg", O_RDONLY);
				
				if(fdimg==-1)
					error_handling("파일open() error!");
				else
				{
					char img_buf[IMG_BUF_SIZE];
					int img_size;	// 실제 이미지 바이트 수
					if((img_size=read(fdimg, img_buf, IMG_BUF_SIZE)==-1))
						error_handling("파일 read() error!");
					else
					{
						char header[]= "HTTP/1.1 200 OK=R=N"
									"Server: Linux Web Server\r\n"
									"Content-Type: image/jpeg\r\n"
									"Content-Length: %ld\r\n\r\n";
						// 헤더 전송
						if(write(clnt_sock, header, strlen(header)) < 0) printf("header write error!!");
						// 이미지 전송
						if(write(clnt_sock, img_buf, sizeof(img_buf)) < 0) printf("image write error!!");												
					}
					close(fdimg);
				}
			}
				
			// 처음 요청이면	
			else
				write(clnt_sock, webpage, strlen(webpage));
		}	
		printf("연결 끊기\n\n");
		close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
