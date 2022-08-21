class RandomizedSet {
private:
    unordered_map<int, list<int>::iterator> um;
    list<int> l;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {

    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (!um.count(val)) {
            l.push_front(val);
            um[val] = l.begin();
            return true;
        }
        return false;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (um.count(val)) {
            auto iter = um[val];
            l.erase(iter);
            um.erase(val);
        }
        return false;
    }

    /** Get a random element from the set. */
    int getRandom() {
        auto idx = rand() % l.size();
        auto iter = next(l.begin(), idx);
        return *iter;
    }
};
