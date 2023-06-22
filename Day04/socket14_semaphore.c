#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void * read(void * arg);
void * accu(void * arg);
static sem_t sem_one;	// static은  변경 불가능하지만  모든곳에서 접근가능
static sem_t sem_two;
static int num;

int main(int argc, char *argv[])
{
	pthread_t id_t1, id_t2;
	sem_init(&sem_one, 0, 0);	// sem_init(sem, pshared, value)	: 세마포어 생성
	sem_init(&sem_two, 0, 1);	// sem: 참조값 저장하고 있는 변수의 주소값 전달
														// pshared: 0이외에는 둘이상 프로세스에의해 접근 가능한 세마포어 생성
														// value: 생성되는 세마포어의 초기 값

	pthread_create(&id_t1, NULL, read, NULL);
	pthread_create(&id_t2, NULL, accu, NULL);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	sem_destroy(&sem_one);	// 세마포어 소멸
	sem_destroy(&sem_two);
	return 0;
}

void* read(void *arg)	// 먼저 실행
{
	int i;
	for(i=0; i<5; i++)
	{
		fputs("Inout num: ", stdout);
		sem_wait(&sem_two);	//	호출되면 sem_two로 부터  키 획득,  세마포어 값을 1감소 -> 0
		scanf("%d", &num);
		sem_post(&sem_one);	//  세마포어 값을 1증가 -> 1
	}
	return NULL;
}

void* accu(void *arg)
{
	int sum=0, i;
	for(i=0; i<5; i++)
	{
		sem_wait(&sem_one);
		sum+=num;
		sem_post(&sem_two);
	}
	printf("Result: %d \n", sum);
	return NULL;
}
