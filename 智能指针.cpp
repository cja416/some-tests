#include<iostream>
#include <string>

using namespace std;

template <typename T>
class Shared_ptr {
public:
	// 空参构造 空指针
	Shared_ptr() :count(0), _ptr((T*)0) {};
	// 构造函数 count必须new出来
	Shared_ptr(T* p) : count(new int(1)), _ptr(p) {};
	// 拷贝构造函数 使其引用次数加一
	Shared_ptr(Shared_ptr<T>& another) :count(&(++ *another.count)), _ptr(another._ptr) {};
	// 重载 operator*和operator-> 实现指针功能
	T* operator->() { return _ptr; };
	T& operator*() { return *_ptr; };
	// 重载operator=
	// 如果原来的Shared_ptr已经有对象，则让其引用次数减一并判断引用是否为零(是否调用delete)。
	// 然后将新的对象引用次数加一。
	Shared_ptr<T>& operator=(Shared_ptr<T>& another) {
		if (this == &another)
			return *this;

		++ *another.count;
		if (this->_ptr && 0 == --*this->count) {	//本指针原有对象计数为1，赋值之后应该析构
			delete count;
			delete _ptr;
			cout << "delete ptr in =" << endl;
		}

		this->_ptr = another._ptr;
		this->count = another.count;
		return *this;
	}

	// 析构函数 使引用次数减一并判断引用是否为零(是否调用delete)。
	~Shared_ptr()
	{
		if (_ptr && 0 == --*count) {
			delete count;
			delete _ptr;
			cout << "delete ptr in ~" << endl;
		}
	}

	int getRef() { return *count; }

private:
	T* _ptr;
	int* count; // should be int*, rather than int
};


int main() {

	Shared_ptr<string> p1(new string("abc"));
	cout << "p1's ref: " << p1.getRef() << " ,p1's obj: " << *p1 << endl;

	Shared_ptr<string> p2(p1);
	cout << "after p2 share with p1: " << endl;
	cout<< "p1's ref: " << p1.getRef() << " ,p1's obj: " << *p1 << endl;
	cout << "p2's ref: " << p2.getRef() << " ,p2's obj: " << *p2 << endl;

	cout << "creat p3 = hello" << endl;
	Shared_ptr<string> p3(new string("hello"));
	cout << "p3's ref: " << p3.getRef() << " ,p3's obj: " << *p3 << endl;

	cout << "after p3 = p2:" << endl;
	p3 = p2;
	cout << "p1's ref: " << p1.getRef() << " ,p1's obj: " << *p1 << endl;
	cout << "p2's ref: " << p2.getRef() << " ,p2's obj: " << *p2 << endl;
	cout << "p3's ref: " << p3.getRef() << " ,p3's obj: " << *p3 << endl;

	system("pause");
	return 0;
}