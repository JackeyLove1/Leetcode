#include <iostream>
#include <unistd.h>
#include <functional>
#include "Thread.h"

using namespace std;

class Foo {
public:
    Foo(int count) : count_(count) {}

    void memFunc() {
        cout << "this is func1 ...  " << endl;
    }

    void memFunc2() {
        while (count_--) {
            cout << "this is func2 ... " << endl;
        }
    }

    void memFunc3(int x) {
        while (count_--) {
            cout << "this is func3 ... " << endl;
        }
    }

private:
    int count_;
};

void ThreadFunc1() {
    cout << "ThreadFunc1 ... " << endl;
}

void ThreadFunc2(int count) {
    while (count--) {
        cout << "ThreadFunc2 ... " << endl;
    }
}

int main() {
    Thread t1(ThreadFunc1);
    Thread t2(bind(ThreadFunc2, 3));
    Foo foo(3);
    Thread t3(bind(&Foo::memFunc2, &foo));

    t1.Start();
    t2.Start();
    t3.Start();

    t1.Join();
    t2.Join();
    t3.Join();

    return 0;
}