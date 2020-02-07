#include <iostream>
#include <string>
#include <sstream>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
class logger;

#define LOG logger(__FILE__, __LINE__).addinfo()

class logger{
public:
	logger(const char* filename, int line)
	:filename(filename),
	 line(line)
	 {
		 fp_=fopen("./simplelog.log","a+");
	 }
	
     	
	 ostream& addinfo(){
		 log<<filename<<' '<<line<<' ';
		 return log;
	 }
	 
	 ~logger(){
		 string tmp = log.str();
		 fwrite(tmp.c_str(), 1, tmp.size(), fp_);
		 fclose(fp_);
		 cout<<"call ~logger()"<<endl;
	 }
	 
	string filename;
	int line;
	ostringstream log;
	FILE* fp_;
};



int main(){
		
	cout<<"begin to log"<<endl;
	
	LOG << "my simple log"<<endl;
	
	cout<<"finish log"<<endl;
	return 0;
}
