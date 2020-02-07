#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/door.h>

using namespace std;

#define DOOR "/data/chenjinan/door.rpc"

void servproc(void* cookie, char* dataptr, size_t datasize, door_desc_t* descptr, size_t ndesc)
{
	long arg,result;
	
	arg = *((long *) dataptr);
	
	result = arg * arg;
	door_return((char*)&result, sizeof(result), NULL,0);
}

int main(){
	
	int fd;

	fd = door_create(servproc,NULL,0);
	
	close(open(DOOR, O_CREAT | O_RDWR));
	fattach(fd,DOOR);
	
	for(;;)
		pause();	//所有工作交给servproc去做。
	
	return 0;
}