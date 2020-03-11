#include <iostream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

volatile int start = 0;

void* func(void *){
	while(1){
		if(start == 1){
			cout << "Thread malloc" << endl;
			char* buf = new char[1000];
			start = 0; 
		}
		sleep(1);
	}
}

int main(){
	pthread_t tid;
	pthread_create(&tid,0,func,0);

	getchar();
	start = 1;

	pthread_join(tid,NULL);
	return 0;
}
