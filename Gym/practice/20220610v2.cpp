//
// Created by Jacky on 2022/6/10.
//

#include <string>
#include <string_view>
#include <iostream>

using std::cout, std::endl;

void *operator new(std::size_t count) {
    cout << "malloc " << count << " memory" << endl;
    return malloc(count);
}

void operator delete(void *p) {
    cout << "delete memory" << endl;
    free(p);
}

void show_string(const std::string &s) {
    cout << "--------------------" << endl;
    std::string t = s;
    cout << "address of s is " << s.c_str() << endl;
    cout << "address of t is " << t.c_str() << endl;
}

void show_string_view(std::string_view sv) {
    cout << "----------" << endl;
    cout << "address of sv is " << sv.data() << endl;
}

int main() {
    std::cout << std::endl;
    std::cout << "-------初始化string对象-------" << std::endl;
    std::string you = "How do you do~,My name is peter!";
    std::cout << std::endl;

    std::cout << "-------初始化string_view对象-------" << std::endl;
    std::string_view stv(you.c_str(), you.size());
    std::cout << std::endl;
    std::cout << "---------show_str---------" << std::endl;
    printf("main函数:you副本中的字符串地址:%p\n", you.c_str());
    show_string(you);

    std::cout << std::endl;
    std::cout << "字符串字面量直接传参方式" << std::endl;
    show_string("How do you do~,My name is peter!");

    std::cout << std::endl;
    std::cout << "---------show_stv----------" << std::endl;
    std::cout << std::endl;
    std::cout << "字符串字面量直接传参方式" << std::endl;
    show_string_view(stv);

    std::cout << std::endl;
    std::cout << "数组字符串传参方式" << std::endl;
    show_string_view("How do you do~,My name is peter!");

    std::cout << std::endl;

    return 0;
}