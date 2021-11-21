#include <iostream>

using namespace std;

template<typename T>
void print(T &t) {
    cout << "T&" << endl;
}

template<typename T>
void print(T &&t) {
    cout << "T&&" << endl;
}

template<typename T>
void TestForward(T &&t) {
    print(t);
    print(std::forward<T>(t));
    print(std::move(t));
}

int main() {
    TestForward(1);
    int x = 1;
    cout << "----------" << endl;
    TestForward(x);
    cout << "----------" << endl;
    TestForward(std::forward<int>(x));
}