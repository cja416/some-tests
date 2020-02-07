#include <stdio.h>  
#include <stdlib.h>  
#include <sys/time.h>  
#include <time.h>  
#include <sched.h>  
#include <sys/types.h>  
#include <unistd.h>      //pipe()  
  
int main()  
{  
    int x, i, fd[2], p[2];  
	//int start=0,end=0,diff=0;
    char send ='s';  
    char receive;  
    pipe(fd);  
    pipe(p);  
    struct timeval tv;  
    struct sched_param param;  
    param.sched_priority = 0;  
					  
    while ((x = fork()) == -1);  //Keep creating until success
    if (x==0) {  
        sched_setscheduler(getpid(), SCHED_FIFO, &param);  
        gettimeofday(&tv, NULL);  
        printf("Before Context Switch Time %u us\n", tv.tv_usec);  
		//start = tv.tv_usec;
        for (i = 0; i < 10000; i++) {  
 	    	read(fd[0], &receive, 1);  //child read and write
            write(p[1], &send, 1);  
        }  
         exit(0); 
    }	 
    else {  
	sched_setscheduler(getpid(), SCHED_FIFO, &param);  
	for (i = 0; i < 10000; i++) {  
	    write(fd[1], &send, 1);  	//father write and read
	    read(p[0], &receive, 1);  
	}  
		gettimeofday(&tv, NULL);  
		//end = tv.tv_usec;
		printf("After Context SWitch Time %u us\n", tv.tv_usec);  
    }  
	//diff = end - start;
	//printf("the diff time of 10000 times pipe transport is %d us \n",diff);//犯了一个错误，start和end的赋值在不同的进程内
	//printf("the context switch of this mechine is about %f us\n", diff*1.0/2/10000);

    return 0;  
}  
