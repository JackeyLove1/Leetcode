//
// Created by Jacky on 2021/11/9.
//

#include "Thread.h"
#include <iostream>

using namespace std;

Thread::Thread() : autoDelete_(false) {
    cout << "Thread ... " << endl;
}

Thread::~Thread() {
    cout << "~Thread ... " << endl;
}

void Thread::Start() {
    pthread_create(&threadId_, nullptr, ThreadRoutine, this);
}

void Thread::Join() {
    pthread_join(threadId_, nullptr);
}

void *Thread::ThreadRoutine(void *arg) {
    auto thread = static_cast<Thread *>(arg);
    thread->Run();
    return nullptr;
}