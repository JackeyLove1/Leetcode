//
// Created by Jacky on 2021/11/9.
//

#include "Thread.h"
#include <iostream>

using namespace std;

Thread::Thread() {
    cout << "Thread ... " << endl;
}

Thread::Thread(const ThreadFunc &func) : autoDelete_(false), func_(func) {
    cout << "Thread with func ... " << endl;
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
    if (thread->autoDelete_) {
        delete thread;
    }
    return nullptr;
}

void Thread::SetAutoDelete() {
    autoDelete_ = true;
}

void Thread::Run() {
    func_();
}