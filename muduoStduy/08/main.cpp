#include <iostream>
#include <unistd.h>
#include "Thread.h"

using namespace std;

class TestThread : public Thread {
private:
    int count_;

    void Run() {
        while (count_--) {
            cout << "run the thread ... " << endl;
            sleep(1);
        }
    }

public:
    TestThread(int count) : count_(count) {
        cout << "TestThread ... " << endl;
    }

    ~TestThread() {
        cout << "~TestThread ... " << endl;
    }
};

int main() {
    TestThread t1(10);
    t1.Start();
    t1.Join();
    return 0;
}s