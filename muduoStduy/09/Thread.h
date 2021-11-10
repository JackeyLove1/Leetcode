//
// Created by Jacky on 2021/11/9.
//

#ifndef STUDY_THREAD_H
#define STUDY_THREAD_H

#include <pthread.h>
#include <functional>

class Thread {
public:
    using ThreadFunc = std::function<void()>;

    Thread();

    Thread(const ThreadFunc &);

    virtual ~Thread();

    void Start();

    void Join();

    void SetAutoDelete();

private:
    void Run();

    static void *ThreadRoutine(void *arg);

    pthread_t threadId_;

    ThreadFunc func_;

    bool autoDelete_;
};

#endif //STUDY_THREAD_H
