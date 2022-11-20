template <typename T>
class BloomFilter {
   public:
    BloomFilter(vector<function<int(T)>> hash_functions) : hash_functions_(hash_functions) {
        flags_.assign(hash_functions_.size(), false);
    }

    void Add(T key) {
        for (auto hash_function : hash_functions_) {
            flags_[hash_function(key)] = true;
        }
    }

    bool MaybeOccurred(T key) {
        for (auto hash_function : hash_functions_) {
            if (!flags_[hash_function(key)]) return false;
        }
        return true;
    }
   private:
    vector<function<int(T)>> hash_functions_;
    vector<bool> flags_;
};