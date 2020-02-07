#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
 
using namespace std;
#define PORT 2333		//端口号
#define BACKLOG 5	//最大监听数

int main()
{
    int serverfd = 0;
    int ret = 0;
    int newfd = 0;
    char buf[4096] = {0};

    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    socklen_t socklen = 0;

    serverfd = socket(AF_INET,SOCK_STREAM,0);
    if(0 > serverfd){
        cout<<"创建socket失败"<<endl;
	return 0;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(0 > bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr))){
	cout<<"绑定失败"<<endl;
	return 0;	
    }

    if(0 > listen(serverfd, BACKLOG))
    {
        cout<<"监听失败"<<endl;
	return 0;
    }

    newfd = accept(serverfd, (struct sockaddr *)&client_addr, &socklen);
    if(0 > newfd){
        cout<<"accept 失败"<<endl;
	return 0;
    }
    else{
        cout<<"accept 成功，服务器会发送一条消息给客户端"<<endl;
	send(newfd, "服务器接收连接成功!", sizeof("服务器接收连接成功!"), 0);
    }

    cout<<"server wait for 3 second, client send message 3 times"<<endl;
    sleep(3);
    ret = recv(newfd, buf, sizeof(buf), 0);

    if(0 >= ret){
        cout<<"client close or recv failed"<<endl;
    }
    else{
	cout<<"ret = " << ret <<endl;
	cout<<"recv message: "<<endl;
	for(int i = 0 ; i < ret ;i++)
		cout<<buf[i]<<' ';
        //cout<<"recv message: "<<buf<<endl;
    }

    close(newfd);
    close(serverfd);

    return 0;
}
