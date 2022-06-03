//
// Created by Jacky on 2022/5/28.
//

#include <limits>
#include <iostream>
#include <memory>

using namespace std;

class A{
public:
    A() {
        cout << "Create" << endl;
    };
    A(const A&) {
        cout << "Copy" << endl;
    };
    A(A&&) {
        cout << "Move" << endl;
    };
    A& operator = (const A&){
        cout <<" Copy = " << endl;
    }

    A&& operator = (A&&){
        cout << "Move = " << endl;
    }
};

A f(A a){
    return a;
}
int main(){
    auto a = f(A());
    auto b = std::move(a);
}