#include <iostream>
#include <unistd.h>
//#include<pthread.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

using namespace std;

int main(){
	
	pid_t pid;
	int pipe_fd[2];
	if(pipe(pipe_fd)<0){
		perror("pipe failed");
		exit(-1);
	}
	
	pid = fork();
	if(pid<0){
		perror("fork failed");
		exit(-1);
	}
	else if(pid == 0){	//子进程
		close(pipe_fd[0]);
		string s;
		cout<<"in child process, please input a string "<<endl;
		cin>>s;
		cout<<"child is going to send " << s.size() << " byte message"<<endl;
		if(write(pipe_fd[1],s.c_str(),s.size()) < 0){
			perror("write error"); exit(-1);
		}
		exit(-1);
	}
	else{				//父进程
		close(pipe_fd[1]);
		cout<<"parent is going to read pipe"<<endl;
		char message[1024];
		ssize_t ret = 0;
		//if(ret=read(pipe_fd[0],message,1024) < 0){
		//	perror("read error"); exit(-1);
		//}
		while((ret=read(pipe_fd[0],message,1024)) > 0)
		    cout<<"parent read "<< ret <<" byte message: " << message <<endl;
		waitpid(pid,NULL,0);
	}
	return 0;
}
