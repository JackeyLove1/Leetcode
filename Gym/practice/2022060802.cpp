//
// Created by Jacky on 2022/6/8.
//

#include <random>
#include <iostream>
#include <functional>
#include <numeric>
#include <string>
#include <boost/version.hpp>

using std::cout, std::endl;

constexpr long fab(long n) {
    return n <= 2 ? 1 : fab(n - 1) + fab(n - 2);
}

constexpr bool is_prime(int n) {
    if (n <= 1) {
        return false;
    } else if (n == 2) {
        return true;
    } else {
        int sq = static_cast<int>(std::sqrt(n)) + 1;
        for (int i = 2; i < sq; ++i) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
}

int main() {
    std::default_random_engine re(std::random_device{}());
    std::normal_distribution<> normal;
    auto normal2 = std::bind(std::normal_distribution<>{},
                             std::default_random_engine(std::random_device{}()));

    for (int i = 0; i < 6; ++i) {
        cout << normal(re) << endl;
        cout << normal2() << endl;
    }

    cout << std::numeric_limits<int>::epsilon() << endl;
    cout << std::numeric_limits<double>::epsilon() << endl;
    cout << "Boost版本：" << BOOST_VERSION << endl;
    cout << fab(10) << endl;
    for (int i = 1; i < 10; ++i) {
        std::string prime = "not prime";
        if (is_prime(i)) {
            prime = "prime";
        }
        cout << i << " is " << prime << endl;
    }
    return 0;
}