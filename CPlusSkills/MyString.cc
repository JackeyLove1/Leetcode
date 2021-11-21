#include <iostream>
#include <cstring>

using namespace std;

class MyString {
private:
    char *m_data;
    size_t m_len;

    void copy_data(const char *s) {
        m_data = new char[m_len + 1];
        memcpy(m_data, s, m_len);
        m_data[m_len] = '\0';
    }

public:
    MyString() {
        m_len = 0;
        m_data = new char[1];
        m_data[0] = '\0';
    }

    MyString(const char *p) {
        m_len = strlen(p);
        copy_data(p);
    }

    MyString(const MyString &mstr) {
        m_len = mstr.m_len;
        copy_data(mstr.m_data);
        std::cout << "run MyString(const MyString &mstr)" << std::endl;
    }

    MyString(MyString &&mstr) {
        m_len = mstr.m_len;
        m_data = mstr.m_data;
        mstr.m_len = 0;
        mstr.m_data = nullptr;
        std::cout << "run MyString(MyString &&mstr)" << std::endl;
    }

    MyString &operator=(const MyString &mstr) {
        if (this != &mstr) {
            m_len = mstr.m_len;
            copy_data(mstr.m_data);
        }
        std::cout << "run MyString &operator=(const MyString &mstr)" << std::endl;
        return *this;
    }

    MyString &operator=(MyString &&mstr) {
        if (this != &mstr) {
            m_len = mstr.m_len;
            m_data = mstr.m_data;
            mstr.m_len = 0;
            mstr.m_data = nullptr;
            std::cout << "run MyString &operator=(MyString &&mstr)" << std::endl;
        }
        return *this;
    }

    ~MyString() {
        delete m_data;
        std::cout << " delete data ... " << std::endl;
    }

    friend ostream &operator<<(ostream &os, const MyString &mstr) {
        os << mstr.m_data << std::endl;
        return os;
    }

};

using namespace std;

int main() {
    MyString s1("hello");
    cout << "s1: " << s1 << endl;
    auto s2(s1);
    cout << "s2: " << s2 << endl;
    auto s3(std::move(s1));
    cout << "s3: " << s3 << endl;
    auto s4 = s3;
    cout << "s4: " << s4 << endl;
    auto s5 = std::move(s4);
    cout << "s5: " << s5 << endl;
}