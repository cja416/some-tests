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

using namespace std;

#define FIFO_fd "/data/chenjinan/fifo.1"

int main(){
	
	int readfd,writefd;
	
	if(mkfifo(FIFO_fd, S_IFIFO|0666) < 0 && (errno != EEXIST)){
		perror("make fifo failed");
		exit(-1);
	}
	
	int pid = fork();
	if(pid<0){
		perror("fork failed");
		exit(-1);
	}
	else if(pid == 0){	//子进程
		writefd = open(FIFO_fd,O_WRONLY);
		string s;
		cout<<"please input a string "<<endl;
		cin>>s;
		if((write(writefd,s.c_str(),s.size())) < 0){
			perror("write error"); exit(-1);
		}
		exit(-1);
	}
	else{				//父进程
		readfd = open(FIFO_fd,O_RDONLY);
		cout<<"parent is going to read pipe"<<endl;
		char message[1024];
		ssize_t ret=0;
		if((ret=read(readfd,message,1024)) < 0){
			perror("read error"); exit(-1);
		}
		cout<<"parent read "<<ret<<" byte message: " << message <<endl;
		waitpid(pid,NULL,0);
	}
        unlink(FIFO_fd);//删除管道文件
	return 0;
}
