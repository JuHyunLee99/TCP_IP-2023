# TCP_IP-2023
TCP/IP 소켓 프로그래밍 학습
## Day01
- 리눅스 명령어 
	- 폴더생성: mkdir
	- 폴더및파일삭제: rm -fr [삭제할 폴더명/파일]
	- 현재 폴더 확인: ls
		- -l: 구체적 출력
		- -a: 숨긴파일도 출력
	- 현재 위치확인: pwd
	- 기본 편집기: nano
	- 폴더이동: cd [이동할 폴더명]
		- ./: 현재폴더
		- ../: 바로 위 폴더로 이동
	- 기본폴더: /home/pi
	- 리눅스 기반에서 컴파일: gcc 파일명.c -o 실행파일명

- 서버소켓
	1. 소켓 생성: socket 함수호출
	2. IP주소와 PORT번호 할당: bind 함수호출
	3. 연결요청 대기상태로의 진입: listen 함수호출
	4. 클라이언트이 연결요청에 대한 수락: accept 함수호출
	
- 클라이언트 소켓
	1. 소켓 생성: socket 함수호출
	2. 서버에 연결요청: connect 함수 호출
- 파일 열기
``` c
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
```
- 파일 닫기
``` c
close(fd);
```
- 파일에 데이터 쓰기
``` c
write(fd, buf, sizeof(buf))
```
- 파일에 저장된 데이터 읽기
```c
read(fd, buf, sizeof(buf))
```
## Day02
- 네트워크 바이트 순서
	- 빅 엔디안(Big Endian): 상위 바이트의 값을 작은 번지수에 저장하는 방식
   	- 리틀 엔디안(Little Endian): 상위 바이트의 값을 큰 번지수에 저장하는 방식 (라즈베리파이os)

- 문자열 정보를 네트워크 바이트 순서의 정수로 변환
  	- inet_addr
  	- inet_aton
  	- inet_ntoa
   	
- 소켓 생성
``` c
serv_sock=socket(PF_INET, SOCK_STREAM, 0);	// 서버 소켓의 파일 디스크립터 저장
// 프로토콜 체계 (Protocol Family)
// - PF_INET: IPv4인터넷 프로토콜 체계
// - PF_INET6: IPv6인터넷 프로토콜 체계
// 소켓의 타입(Type): 데이터 전송 방식
// - SOCK_STREAM: 연결지향형 소켓 TCP
// - SOCK_DGRAM: 비 연결지향형 소켓 UDP
// 프로토콜의 최종선택 (동일한 프로토콜이 둘 이상 존재하는 경우)
// - IPPROTO_TCP
// - IPPROTO_UDP
```

- IPv4 기반의 주소표현을 위한 구조체
	- sockaddr_in
   	- in_addr
``` c
memset(&serv_addr, 0, sizeof(serv_addr));	// 구조체 serv_addr 을  0으로 초기화
	serv_addr.sin_family=AF_INET;		// 주소체계(Address Family)
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); // 32bit IPv4 인터넷 주소 
 	// INADDR_ANY: 소켓이 동작하는 컴퓨터의 IP주소 자동으로 할당
	serv_addr.sin_port=htons(atoi(argv[1]));	// 16비트 TCP PORT 번호
	// 두번째 명령어(포트)를 변환해서 할당
 
 	// 네트워크 바이트순서 변환
  	// hton , htons 
   	// host_port와 host_addr에 저장된 데이트를 네트워크 바이트 순서로 변환
 ```
- IP주소와 PORT번호 할당
``` c
// serv_sock에 serv_addr에 담기  정보를 할당
if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
	error_handling("bind() error");
```
- 연결요청 가능상태로 변경 = 연결요청 대기상태로의 진입
``` c
if(listen(serv_sock, 5)==-1)
	error_handling("listen() error");
  ```
- 연결요청에 대한 수락
``` c
clnt_addr_size=sizeof(clnt_addr);

//  클라이어트 소켓이 만들어짐
clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
if(clnt_sock==-1)
	error_handling("accept() error");
```

## Day05
- Iterative 에코 서버, 에코 클라이언트
	- socket01_echo_client.c 문제점
		- 문자열 단위의 에코에 적절하지 않음.
		- TCP는 데이터의 경계 존재 없음.
		- 둘 이상의 Write 함수호출로 전달된 문자열 정보가 묶여서 한번에 서버로 전송될 가능성있음.
		- 클라이언트는 한번에 둘이상의 문자열 정보를 서버로부터 돌려받아서 원하는 결과를 얻지 못할 가능성 있음.
		- 전송할 데이터의 크기가 크다면 운영체제가 여러 패킷으로 나눠서 전송할 수도 있음.
		- 클라이언트느 다 전송되기전에 read함수가 호출될 수도 있음.
	- socket02_echo_client2 해결책
		- 클라이언트가 수신해야할 데이트의 크기를 미리 알고 있기때문에 데이터 크기를 비교하여 read
	- 어플리케이션 프로토콜
		- 수신할 데이터의 크기를 파악하는 것이 불가능할경우
		- Q가 전달되면 연결을 종료한다 약속
	- UDP
	- Half-close 기반의 파일전송 프로그램
		- shutdown 함수
## Day04
- IP주소와 도메인 이름
```c
// 도메인 이름으로부터 IP의 주소정보를 얻는 함수 
host=gethostbyname(argv[1]);	// 성공시 hostent 구조체 변수의 주소값, 실패시 NULL
if(!host)	// 실패시
	error_handling("gethost... error");
```
	- 구조체 hostent
 ```c
printf("official name: %s \n", host->h_name);	// 공식 도메인 이름
for(i=0; host->h_aliases[i]; i++)
	printf("Aliases %d: %s \n", i+1, host->h_aliases[i]);	// 공식 도메인 이름 외에에 접속할 수 있는 다른 도메인이름
printf("Address type: %s \n",
		(host->h_addrtype==AF_INET)?"AF_INET":"AF_INET6");	// IP 주소체계
for(i=0; host->h_addr_list[i]; i++)		// 도메인 이름에 대한 정수 형태의 IP주소들의 리스트
	printf("IP addr %d: %s \n", i+1,
		inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
// h_length : IP주소 크기정보
```
			
	
