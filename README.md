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
```
