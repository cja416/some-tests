#include<iostream>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

using namespace std;

#define NUM 5
int queue[NUM];

int producer_num = 1;
int consumer_num = 1;
sem_t blank_num,product_num;

void* produce(void* arg){
	int i=0;
	
	while(1){
		sem_wait(&blank_num);	//等待空格子
		queue[i]=rand()%100 +1;
		sem_post(&product_num);
		i=(i+1)%NUM;
	}
}

void* consume(void* arg){
	int i=0;
	
	while(1){
		sem_wait(&product_num);	//等待产品
		queue[i]=0;			//消费产品
		cout<< "i consume 1 product" << endl;
		sem_post(&blank_num);
		i=(i+1)%NUM;
	}
}

int main(){

	sem_init(&blank_num,0,NUM);  //初始空格NUM个
	sem_init(&product_num,0,0);	//初始产品0个

	pthread_t t_producers[producer_num];
	pthread_t t_consumers[consumer_num];
	
	for(int i=0;i<producer_num;i++){
		t_producers[i]=0;
		pthread_create(&t_producers[i],NULL,produce,NULL);
	}
	
	 for(int i=0;i<consumer_num;i++){
		t_consumers[i]=0;
		pthread_create(&t_consumers[i],NULL,consume,NULL);
	}
	 
	 for(int i=0;i<producer_num;i++){
		pthread_join(t_producers[i],NULL);
	}
	
	 for(int i=0;i<consumer_num;i++){
		pthread_join(t_consumers[i],NULL);
	}
	 
	 sem_destroy(&blank_num);
	 sem_destroy(&product_num);
	 
	return 0;
}
