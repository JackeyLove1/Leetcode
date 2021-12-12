#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class ThroneInheritance {
private:
    string king;
    unordered_map<string, vector<string>> m_;
    unordered_map<string, bool> death_;
public:
    ThroneInheritance(string kingName) : king(kingName) {

    }

    void birth(string parentName, string childName) {
        m_[parentName].emplace_back(childName);
    }

    void death(string name) {
        death_[name] = true;
    }

    // 使用递归技术
    vector<string> getSons(const string &parent) {
        vector<string> sons;
        if (m_.count(parent)) {
            for (auto &son : m_[parent]) {
                if (!death_.count(son)) sons.push_back(son);
                auto sonStrings = getSons(son);
                if (sonStrings.empty()) continue;
                sons.insert(sons.end(), sonStrings.begin(), sonStrings.end());
            }
        }
        return sons;
    }


    vector<string> getInheritanceOrder() {
        auto res = getSons(king);
        if (!death_.count(king)) res.insert(res.begin(), king);
        return res;
    }
};

int main() {

}