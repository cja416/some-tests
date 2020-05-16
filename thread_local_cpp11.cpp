//thread_local 测试
#include<iostream>
#include<thread>
#include<mutex>

thread_local int x = 1;
void func(){
    for(int i = 0 ; i < 4; i++)
    {
        x++;
        printf("%ld: %d\n",std::this_thread::get_id() , x);
    }
}

int main()
{
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
    return 0;
}

