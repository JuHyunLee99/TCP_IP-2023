#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREAD 100

void* thread_inc(void* arg);
void* thread_des(void* arg);
long long num=0;	// 64bit 정수 자료형
pthread_mutex_t mutex;

int main(int argc, char *arg)
{
	pthread_t thread_id[NUM_THREAD];	// 쓰레드 id 100개
	int i;

	pthread_mutex_init(&mutex, NULL);
	
	for(i=0; i<NUM_THREAD; i++)	// 쓰레드 100개 생성
	{
		if(i%2)	// 홀수
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		else	// 짝수
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
	}

	for(i=0; i<NUM_THREAD; i++)
		pthread_join(thread_id[i], NULL);	// 쓰레드 끝알때까지 프로세스 종료 대기

	printf("result: %lld \n", num);
	pthread_mutex_destroy(&mutex);
	return 0;
}

void* thread_inc(void *arg)
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i=0; i<50000000; i++)
		num+=1;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void* thread_des(void *arg)
{
	int i;
	for(i=0; i<50000000; i++)
	{
		pthread_mutex_lock(&mutex);
		num-=1;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

// 문제점 발생 여러 쓰레드로 레지스터의 데이터를 동시에 접근하고 바꿔서 원하는 값이 안나옴. socket13에서 봅시당
// mutex
