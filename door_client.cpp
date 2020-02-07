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

int main(){
	
	
	int fd;
	long ival,oval;
	door_arg_t arg;
	
	fd = open(DOOR,O_RDWR);
	
	ival = 1000000;
	arg.data_ptr = (char*) &ival;
	arg.data_size = sizeof(long);	//输入参数
	arg.desc_ptr = NULL;
	arg.desc_num = 0;	//处理描述符的传递
	arg.rbuf = (char*) &oval;
	arg.rsize = sizeof(long);	//输出结果
	
	door_call(fd, &arg);
	
	cout<<"result is "<<oval<<endl;
	
	return 0;
}