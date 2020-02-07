#include<iostream>
#include<pthread.h>

using namespace std;

pthread_mutex_t mutex;
int k=0;
pthread_cond_t cond;	

void *func1(void *arg){
    for(int i = 0 ; i<10; i++){
	pthread_mutex_lock(&mutex);
            while(k%3!=0){
		pthread_cond_wait(&cond,&mutex);
            }
		cout<<"A";
                k++;
            pthread_mutex_unlock(&mutex);
            pthread_cond_broadcast(&cond);
	
    }
}

void *func2(void *arg){
    for(int i = 0 ; i<10; i++){
	 pthread_mutex_lock(&mutex);
            while(k%3!=1){
		pthread_cond_wait(&cond,&mutex);
            }
		cout<<"B";
                k++;
            pthread_mutex_unlock(&mutex);
            pthread_cond_broadcast(&cond);
	
    }
}

void *func3(void *arg){
    for(int i = 0 ; i<10; i++){
	pthread_mutex_lock(&mutex);
            while(k%3!=2){
		pthread_cond_wait(&cond,&mutex);
            }
		cout<<"C";
                k++;
            pthread_mutex_unlock(&mutex);
            pthread_cond_broadcast(&cond);
	
    }
}

int main(){
	
    pthread_mutex_init(&mutex, NULL);
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    
    pthread_create(&tid1,NULL,func1,NULL);
    pthread_create(&tid2,NULL,func2,NULL);
    pthread_create(&tid3,NULL,func3,NULL);

 //   cout<<"pthread create success!"<<endl;
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    pthread_mutex_destroy(&mutex);
    cout<<endl;
    return 0;
}
