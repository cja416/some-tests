#include<iostream>
using namespace std;

class DownloadSink{
public:
	virtual void OnDownloadFinished(const char* pURL, bool bOK) = 0; 

};

class MyDownloader{
public:
	MyDownloader(DownloadSink* pSink)
		:m_pSink(pSink){}

	void DownloadFile(const char* pURL){
		cout<<"downloading: "<<pURL<<endl;
		if(m_pSink!=NULL){
			m_pSink->OnDownloadFinished(pURL,true);
		}
	}

private:
	DownloadSink* m_pSink;
};


class MyFile : public DownloadSink
{
public: 
	void download(const char* pURL){
		MyDownloader downloader(this);			//把本类的指针给它，它才能回调本类的非静态成员函数
		downloader.DownloadFile(pURL);
	}
	virtual void OnDownloadFinished(const char* pURL, bool bOK){
		cout << "OnDownloadFinished, URL: "<< pURL<< " status: " << bOK <<endl; 
	}

};

int main(){
	MyFile my_file;
	my_file.download("www.qq.com");
	return 0;
}
