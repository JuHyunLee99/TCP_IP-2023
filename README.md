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
	3. 연결요청 가능상태로 변경 listen 함수호출
	4. 연결요청에 대한 수락: accept 함수호출
	
- 클라이언트 소켓
	1. 소켓 생성: socket 함수호출
	2. 서버에 연결요청: connect 함수 호출

##Day02
- 소켓 생성
``` c
serv_sock=socket(PF_INET, SOCK_STREAM, 0);
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
	serv_addr.sin_port=htons(atoi(argv[1]));	// 16비트 TCP PORT 번호
	// 두번째 명령어(포트)를 변환해서 할당
 ```
