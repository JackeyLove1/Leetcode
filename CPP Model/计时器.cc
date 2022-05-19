//
// Created by Jacky on 2022/5/18.
//

#include <chrono>
#include <cstdio>
#include <iostream>

class Timer final {
public:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;

    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float ms = duration.count() * 1000.0f;
        printf("Timer took %.4f ms\n", ms);
    }
};


int main() {
    {
        Timer t;
        for (int i = 0; i < 100; ++i) {
            std::cout << "Hello, World" << std::endl;
        }
    }
    {
        Timer t;
        for (int i = 0; i < 100; ++i) {
            std::cout << "Hello, World\n";
        }
    }
    {
        Timer t;
        for (int i = 0; i < 100; ++i) {
            printf("Hello, World\n");
        }
    }
}