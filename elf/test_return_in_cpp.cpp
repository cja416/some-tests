#include <iostream>
using namespace std;
 
//构造函数与赋值运算符的区别是，构造函数在创建或初始化对象的时候调用，而赋值运算符在更新一个对象的值时调用。
 
class A {
public:
	A(int a):x(a) { cout << "调用了构造函数" << endl; }
	A& operator=(const A& a) { cout << "调用了赋值构造函数" << endl; this->x = a.x; return *this; }
	A(const A& a):x(a.x){ cout << "调用了拷贝构造函数" << endl; }
	A(const A&& a):x(a.x){ cout << "调用了移动构造函数" << endl; }
	A& operator=(const A&& a) { cout << "调用了移动赋值构造函数" << endl; this->x = a.x;  return *this; }
	~A(){ cout << "调用了析构函数" << endl; }
 
	int x;
};
 
A func() {
	A a(1);
	cout<<"before return in func"<<endl;
	return a;
}
 
A GetA()
{
	return A(1);
}
 
A&& MoveA()
{
	return A(1);
}
 
 
int main() {
 	A qq(0);
	qq = func();
 
	//system("pause");
	return 0;
}
