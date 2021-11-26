#include <iostream>
#include <unordered_map>
#include <list>
#include <stdexcept>

template<typename K, typename V>
class lru_cache {
private:
    typedef std::pair<K, V> cache_entry;
    typedef std::list<cache_entry> cache_list;
    typedef std::unordered_map<K, typename cache_list::iterator> cache_map;

public:
    typedef typename cache_list::iterator iterator;
    typedef typename cache_list::const_iterator const_iterator;

    lru_cache(size_t size) : size_(size) {
        cache_map_.reserve(size_);
    }

    void add(const K &key, const V &value) {
        if (cache_map_.size() >= size_)
            remove_eldest();

        auto map_it = cache_map_.find(key);
        if (map_it == cache_map_.end()) {
            // Add element to list and save iterator on map
            auto list_it = cache_list_.insert(cache_list_.begin(), std::make_pair(key, value));
            cache_map_.emplace(key, list_it);
        } else {
            // Copy entry from list
            auto &list_it = map_it->second;
            cache_entry entry = *list_it;

            // Remove entry from list
            cache_list_.erase(list_it);

            // Update entry and add to beginning of the list
            entry.second = value;
            cache_list_.push_front(entry);
        }
    }

    V remove(const K &key) {
        auto map_it = cache_map_.find(key);
        if (map_it == cache_map_.end())
            throw std::runtime_error("key not found");

        auto &list_it = map_it->second;
        cache_map_.erase(map_it);
        cache_entry entry = *list_it;
        cache_list_.erase(list_it);
        return entry.second;
    }

    V remove_eldest() {
        if (cache_map_.empty())
            throw std::runtime_error("cache is empty");

        cache_entry entry = cache_list_.back();
        cache_map_.erase(entry.first);
        cache_list_.pop_back();
        return entry.second;
    }

    iterator begin() {
        return cache_list_.begin();
    }

    iterator end() {
        return cache_list_.end();
    }

    const_iterator cbegin() const {
        return cache_list_.cbegin();
    }

    const_iterator cend() const {
        return cache_list_.cend();
    }

    size_t size() const {
        return cache_map_.size();
    }

    bool empty() const {
        return cache_map_.empty();
    }

private:
    size_t size_;
    cache_map cache_map_;
    cache_list cache_list_;
};

int main() {
    lru_cache<std::string, int> cache(3);
    cache.add("one", 1);
    cache.add("two", 2);
    cache.add("three", 3);
    cache.add("four", 4);
    std::cout << cache.size() << std::endl;
    std::cout << cache.remove("four") << std::endl;
    std::cout << cache.size() << std::endl;

    for (const auto &p : cache)
        std::cout << p.first << " = " << p.second << std::endl;

    return 0;
} 