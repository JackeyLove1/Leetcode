#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstring>
#include <string>
#include <string_view>
#include <list>
#include <cassert>

// using namespace std;

template<typename K, typename V>
class LRU {

public:
    using cache_entry = std::pair<K, V>;
    using cache_list = std::list<cache_entry>;
    using cache_map = std::unordered_map<K, typename cache_list::iterator>;

public:
    using iterator = typename cache_list::iterator;
    using const_iterator = typename cache_list::const_iterator;

public:
    explicit LRU(size_t size) : size_(size) {
        assert(size_ > 0);
        cacheMap.reserve(size);
    }

    void add(const K &key, const V &value);

    V remove(const K &key);

    V remove_oldest();

    iterator begin() { return cacheList.begin(); };

    iterator end() { return cacheList.end(); };

    size_t size() const { return cacheMap.size(); };

    bool empty() const { return size_ == 0; };

private:
    size_t size_;
    cache_list cacheList;
    cache_map cacheMap;

};


template<typename K, typename V>
void LRU<K, V>::add(const K &key, const V &value) {
    if (cacheMap.size() >= size_) {
        remove_oldest();
    }
    auto iter = cacheMap.find(key);
    if (iter == cacheMap.end()) { // insert
        auto &&new_pair = std::make_pair(key, value);
        auto new_iter = cacheList.insert(cacheList.begin(), new_pair);
        cacheMap[key] = new_iter;
    } else { // replace
        auto &old_iter = cacheMap[key];
        auto new_entry = *old_iter;
        new_entry.second = value;
        cacheList.erase(old_iter);
        // cacheList.push_front(new_entry);
        auto new_iter = cacheList.insert(cacheList.begin(), std::move(new_entry));
        cacheMap[key] = new_iter;
    }
}

template<typename K, typename V>
V LRU<K, V>::remove(const K &key) {
    if (cacheMap.find(key) == cacheMap.end()) {
        throw std::runtime_error("Remove the invalid key!");
    }
    auto &old_iter = cacheMap[key];
    auto value = (*old_iter).second;
    cacheMap.erase(key);
    cacheList.erase(old_iter);
    return value;
}

template<typename K, typename V>
V LRU<K, V>::remove_oldest() {
    // assert(!cacheMap.empty());
    if (cacheMap.empty()) {
        throw std::runtime_error("delete oldest from empty list!");
    }
    auto&[key, value] = cacheList.back();
    cacheMap.erase(key);
    cacheList.pop_back();
    return value;
}

int main() {
    LRU<std::string, int> cache(3);
    cache.add("one", 1);
    cache.add("two", 2);
    cache.add("three", 3);
    cache.add("four", 4);
    std::cout << cache.size() << std::endl;
    std::cout << cache.remove("four") << std::endl;
    std::cout << cache.size() << std::endl;
    for (const auto &p : cache) {
        std::cout << p.first << " = " << p.second << std::endl;
    }
    return 0;
}