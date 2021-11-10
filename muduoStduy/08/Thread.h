//
// Created by Jacky on 2021/11/9.
//

#ifndef STUDY_THREAD_H
#define STUDY_THREAD_H

#include <pthread.h>

class Thread {
public:
    Thread();

    virtual ~Thread();

    void Start();

    void Join();

private:
    virtual void Run() = 0;

    static void *ThreadRoutine(void *arg);

    pthread_t threadId_;

    bool autoDelete_;
};

#endif //STUDY_THREAD_H
