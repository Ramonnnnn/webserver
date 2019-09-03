#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void insert1(int *i);
int remove1(int *i);
	int g = 10;
	size_t x = 1;
	size_t y = 10;
	size_t z = 0;
	sem_t sema1;
	sem_t empty;
	sem_t full;

	int products[10] = {};
	//int numbers[10] = {1,2,3,4,5,6,7,8,9,10};
	
void * producer(void *x)
{	

	int i = 0;
	while (i <= g)
	{
		++i;
		sem_wait(&empty); /*down */
		sem_wait(&sema1);
		printf("\ninserted: %d\n", i%10);
		insert1(&i);
		
		sem_post(&sema1);
		sem_post(&full); /*up*/
	}


}


void * consumer(void *x)
{
	int item;
	int i = 0;
	while (i <= g)
	{
		sleep(10);
		++i;
		sem_wait(&full);
		sem_wait(&sema1);
		printf("\nremoved: %d\n", i%10);		
		item = (int)remove1(&i);
		
		sem_post(&sema1);		
		sem_post(&empty);
	}

}


void insert1(int *i)
{
	products[(*i)%10] = *i;
}

int remove1(int *i)
{
	return products[(*i)%10];
}

int main()
{
	sem_init(&sema1, 0, x);
	sem_init(&empty, 0, y);
	sem_init(&full, 0, z);
	
	pthread_t producer_t;
	pthread_t consumer_t;
	pthread_create(&producer_t, NULL, &producer, NULL);
	pthread_create(&consumer_t, NULL, &consumer, NULL);
	pthread_join(producer_t, NULL);
	pthread_join(consumer_t, NULL);
	
	
	return 1;
}



//ensure the thread's own mutex is unlocked, 
	//for scenarios of sharing a thread object between threads:
	//Guard guard(m_mutex); needed??? not if use sharedPtr
























