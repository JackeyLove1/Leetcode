//
// Created by Jacky on 2022/5/17.
//

#include "../include/mymath.h"
#include "../include/static/hello.h"
#include <iostream>

using namespace std;

int main() {
    cout << add(1, 2) << endl;
    cout << add(1.1, 2.2) << endl;
    Hello h;
    h.print();
    return 0;
}