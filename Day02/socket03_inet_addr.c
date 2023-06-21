// 문자열 정보를 네트워크 바이트 순서의 정수로 변환하기
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char *addr1="1.2.3.4";
	char *addr2="1.2.3.256";
	// 성공시 빅 엔디안으로 변환된 32비트 정수 값
	unsigned long conv_addr=inet_addr(addr1);
	if(conv_addr==INADDR_NONE)
		printf("Error occured! \n");
	else
		printf("Network ordered integer addr: %#lx \n", conv_addr);
	// 최대 크기의 정수 255이므로 잘못된 IP주소 -> inet_addr함수의 오류 검출능력 확인할 수 있음.
	conv_addr=inet_addr(addr2);
	if(conv_addr==INADDR_NONE)
		printf("Error occureded \n");
	else
		printf("Network ordered integer addr: %#lx \n\n", conv_addr);
	return 0;
}
