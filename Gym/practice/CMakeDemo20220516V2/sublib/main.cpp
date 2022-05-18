//
// Created by Jacky on 2022/5/17.
//

#include "../sublib1/include/sub1/hello.h"
#include "../sublib2/include/world.h"
#include <iostream>

using std::string;

int main() {
    Hello h;
    World w;
    string s = h.hello() + w.world();
    std::cout << s << std::endl;
    return 0;
}