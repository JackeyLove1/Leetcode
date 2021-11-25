#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <atomic>
#include <shared_mutex>
#include <cassert>

struct LRUHandle;

class Cache {
public:
    Cache() = default;

    Cache(const Cache &) = delete;

    Cache &operator=(const Cache &) = delete;

    virtual ~Cache() {};

    virtual LRUHandle *Insert(const std::string &key, const std::string &value) = 0;

    virtual LRUHandle *Lookup(const std::string &key) = 0;

    virtual void Erase(const std::string &key) = 0;

    // virtual size_t TotalCharge() const ;

};

struct LRUHandle {
    LRUHandle *prev;
    LRUHandle *next;

    std::string key;
    std::string value;

    size_t charge;

    explicit LRUHandle() : prev(nullptr), next(nullptr) {}

    explicit LRUHandle(std::string key_, std::string value_)
            : key(std::move(key_)), value(std::move(value_)),
              prev(nullptr), next(nullptr),
              charge(key.size() + value.size()) {}

    ~LRUHandle() {
        // delete prev; // ?
        // delete next; // ?
    }
};


// A single shared of shared cache
class LRUCache {
private:
    // dummy head of LRU list
    LRUHandle *head_;
    // dummy tail of LRU list;
    LRUHandle *tail_;

private:
    // RW lock
    mutable std::shared_mutex rw_mutex_;

    size_t size_;

    size_t capacity_;

    std::atomic<size_t> memory_usage_;

    // use unordered_map as the base
    std::unordered_map<std::string, LRUHandle *> cache_;

private:
    void LRU_Remove(LRUHandle *e);

    void LRU_Append(LRUHandle *e);

    LRUHandle *LRU_RemoveTail();

    void LRU_MoveToHead(LRUHandle *e);

    void Ref(LRUHandle *e);

    void UnRef(LRUHandle *e);

public:
    LRUCache();

    ~LRUCache();

    void SetCapacity(size_t capacity) { capacity_ = capacity; }

    LRUHandle *Insert(const std::string &key, const std::string &value);

    LRUHandle *Lookup(const std::string &key);

    void Erase(const std::string &key);

    void Prune();

    size_t TotalCharge() const {
        return memory_usage_.load();
    }
};

// link the head and the tail
// head -> lru_, tail_ -> in_use_
LRUCache::LRUCache() : capacity_(0), memory_usage_(0), size_(0) {
    head_ = new LRUHandle();
    tail_ = new LRUHandle();
    head_->next = tail_;
    head_->prev = tail_;
    tail_->next = head_;
    tail_->prev = head_;
}

LRUCache::~LRUCache() {
    LRUHandle *p;
    if (head_ == tail_) return;
    while (head_ != tail_) {
        p = head_->next;
        delete head_;
        head_ = p;
    }
    delete tail_;
}

// move from cold chain to hot chain
void LRUCache::Ref(LRUHandle *e) {

}

// move from hot chain to old chain if refs == 1
// or delete if refs == 0
void LRUCache::UnRef(LRUHandle *e) {

}

// remove e from the double list
void LRUCache::LRU_Remove(LRUHandle *e) {
    e->next->prev = e->prev;
    e->prev->next = e->next;
}

// add e to the front of the double list
void LRUCache::LRU_Append(LRUHandle *e) {
    assert(e != nullptr);
    e->prev = head_;
    e->next = head_->next;
    head_->next->prev = e;
    head_->next = e;
}

// remove the tail from the double list
LRUHandle *LRUCache::LRU_RemoveTail() {
    assert(tail_->prev != head_);
    auto node = tail_->prev;
    LRU_Remove(node);
    return node;
}

void LRUCache::LRU_MoveToHead(LRUHandle *e) {
    assert(e != nullptr);
    LRU_Remove(e);
    LRU_Append(e);
}


LRUHandle *LRUCache::Lookup(const std::string &key) {
    std::shared_lock lk(rw_mutex_);
    if (!cache_.count(key)) {
        return nullptr;
    }
    return cache_[key];
}

LRUHandle *LRUCache::Insert(const std::string &key, const std::string &value) {
    std::unique_lock lk(rw_mutex_);
    if (!cache_.count(key)) {
        LRUHandle *node = new LRUHandle(key, value);
        LRU_Append(node);
        if (++size_ > capacity_) {
            LRUHandle *p = LRU_RemoveTail();
            cache_.erase(p->key);
            delete p;
            p = nullptr;
            --size_;
        }
        return node;
    } else {
        LRUHandle *p = cache_[key];
        p->value = value;
        LRU_MoveToHead(p);
        return p;
    }
}

void LRUCache::Erase(const std::string &key) {
    std::unique_lock lk(rw_mutex_);
    if (!cache_.count(key)) {
        return;
    }
    LRUHandle *p = cache_[key];
    cache_.erase(p->key);
    delete p;
    p = nullptr;
    --size_;
}

void LRUCache::Prune() {

}

static constexpr int kNumSharedBits = 4;
static const int kNumShards = 1 << kNumSharedBits;

class SharedLRUCache : public Cache {
private:
    LRUCache shard_[kNumShards];
    uint64_t last_id_;
public:
    explicit SharedLRUCache(size_t capacity) : last_id_(0) {
        const size_t per_shard = (capacity + (kNumShards - 1)) / kNumShards;
        for (int s = 0; s < kNumShards; ++s) {
            shard_[s].SetCapacity(per_shard);
        }
    }

    ~SharedLRUCache() override = default;

    auto Hash(const std::string &key) {
        return std::hash<std::string>{}(key);
    }

    LRUHandle *Insert(const std::string &key, const std::string &value) override {
        auto hashCode = Hash(key);
        size_t index = hashCode % kNumShards;
        return shard_[index].Insert(key, value);
    }

    LRUHandle *Lookup(const std::string &key) override {
        auto hashCode = Hash(key);
        size_t index = hashCode % kNumShards;
        return shard_[index].Lookup(key);
    }

    void Erase(const std::string &key) override {
        auto hashCode = Hash(key);
        size_t index = hashCode % kNumShards;
        shard_[index].Erase(key);
    }

};

Cache *NewCache(size_t capacity) {
    return new SharedLRUCache(capacity);
}

using namespace std;

int main() {
    auto lru = NewCache(100);
    string k = "hello", v = "world!";
    lru->Insert(k, v);
    // lru->Insert("hehe", "hehehev");
    cout << lru->Lookup(k)->value << v << endl;
}