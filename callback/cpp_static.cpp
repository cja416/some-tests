#include<iostream>
using namespace std;

class Callback
{
	public:
	typedef void(*pFun)(void);
	static void TextPrint(void){
		cout<<"static callback function of a class "<<endl;
	}
};

void ForText(Callback::pFun func){
	func();
}

int main(){
	ForText(Callback::TextPrint);
	return 0;
}
