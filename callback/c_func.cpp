#include<iostream>
using namespace std;

typedef void(*DownloadCallback)(const char* pURL, bool bOK);
void DownloadFile(const char* pURL,DownloadCallback callback){
	cout<<"Downloading: "<<pURL<<" "<<endl;
	callback(pURL,true);
}

void cb(const char* pURL, bool bOK){
	cout << "DownloadFinished, URL "<<pURL<<" status: "<<bOK<<endl;
}

int main(){
	DownloadFile("www.baidu.com",&cb);
	return 0;
}
