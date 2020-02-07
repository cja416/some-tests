#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string> 
using namespace std;

#define PORT 2333			//目标地址端口号
#define SERVER_IP "127.0.0.1" //目标地址IP

int main(){
    int client_fd = 0;
    struct sockaddr_in server_addr = {0};
    char buf[4096] = {0};

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(0 > client_fd){
	cout<<"创建socket失败!"<<endl;
	return 0;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if(0 > connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))){
        cout<<"connect failed"<<endl;
    }
    else{
        cout<<"connect success!"<<endl;
	recv(client_fd,buf,sizeof(buf),0);
	cout<<"recv: "<<buf<<endl;
    }

    for(int i=1;i<=3;i++){
	string s = "this is ";
        s = s + to_string(i);
        s = s + " th message.";	
        send(client_fd,"test",sizeof("test"),0);
	cout<<"this time i send: "<< "test" << endl;
    }

    close(client_fd);
    return 0;
}
