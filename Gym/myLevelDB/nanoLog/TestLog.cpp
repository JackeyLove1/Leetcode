//
// Created by Jacky on 2021/12/8.
//

#include <iostream>
#include "Logger.h"

using namespace std;

void TestSingleThread() {
    Logger l;
    l.initLogger();
    const int N = 10000;
    const string msg = "hello, world!";
    const string type = "INFO";
    auto start = chrono::steady_clock::now();

    for (int i = 0; i < N; ++i) {
        l.writetest(msg);
    }
    l.flush();
    auto end = chrono::steady_clock::now();

    auto time_diff = end - start;
    auto duration = chrono::duration_cast<chrono::milliseconds>(time_diff);
    cout << "write bytes: " << l.getMemoryUsage() << endl;
    cout << "Operation cost : " << duration.count() << "ms" << endl;
    l.shutDown();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}