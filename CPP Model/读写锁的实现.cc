//
// Created by Jacky on 2022/5/18.
//

#include <mutex>
#include <iostream>

using namespace std;

class RWLock {
private:
    std::mutex readMutex_;
    std::mutex writeMutex_;
    int readCount_;
public:
    RWLock() : readCount_(0) {}

    void RLock() {
        readMutex_.lock();
        if (++readCount_ == 1) {
            writeMutex_.lock();
        }
        readMutex_.unlock();
    }

    void RUnLock() {
        readMutex_.lock();
        if (--readCount_ == 0) {
            writeMutex_.unlock();
        }
        readMutex_.unlock();
    }

    void WLock() {
        writeMutex_.lock();
    }

    void WUnLock() {
        writeMutex_.unlock();
    }
};