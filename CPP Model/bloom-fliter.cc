bool CheckLittleEndian() {
    union {
        short inum = 0x1234;
        char cnum;
    } dummy;
    return dummy.cnum != 0x12;
}

uint32_t DecodeFixed32(const char *ptr) {
    if (!ptr) {
        return 0;
    }
    if (CheckLittleEndian()) {
        // Load the raw bytes
        uint32_t result = 0;
        memcpy(&result, ptr, sizeof(result));  // gcc optimizes this to a plain load
        return result;
    } else {
        return ((static_cast<uint32_t>(static_cast<unsigned char>(ptr[0]))) |
                (static_cast<uint32_t>(static_cast<unsigned char>(ptr[1])) << 8) |
                (static_cast<uint32_t>(static_cast<unsigned char>(ptr[2])) << 16) |
                (static_cast<uint32_t>(static_cast<unsigned char>(ptr[3])) << 24));
    }
}

uint32_t Hash(const char *data, uint32_t len) {
    if (len <= 0 || !data) {
        return 0;
    }
    static constexpr uint32_t seed = 0xbc9f1d34;
    // Similar to murmur hash
    static constexpr uint32_t m = 0xc6a4a793;
    static constexpr uint32_t r = 24;
    const char *limit = data + len;
    uint32_t h = seed ^(len * m);

    // Pick up four bytes at a time
    while (data + 4 <= limit) {
        uint32_t w = DecodeFixed32(data);
        data += 4;
        h += w;
        h *= m;
        h ^= (h >> 16);
    }
    switch (limit - data) {
        case 3:
            h += static_cast<uint8_t>(data[2]) << 16;
        case 2:
            h += static_cast<uint8_t>(data[1]) << 8;
        case 1:
            h += static_cast<uint8_t>(data[0]);
            h *= m;
            h ^= (h >> r);
            break;
    }
    return h;
}

class BloomFilter {
public:
    //直接给定每个key占的位数
    BloomFilter(int32_t bits_per_key);

    //通过误差率反算出每个key所占的位数
    BloomFilter(int32_t entries_num, float positive);

    ~BloomFilter() = default;

    const char *Name() ;

    void CreateFilter(const std::string_view *keys, int32_t n) ;

    bool MayMatch(const std::string_view &key, int32_t start_pos, int32_t len) ;

    uint32_t Size() {
        return bloomfilter_data_.size();
    }

private:
    void CalcBloomBitsPerKey(int32_t entries_num, float positive = 0.01);

    void CalcHashNum();

private:
    // 每个key占用的bit位数
    int32_t bits_per_key_ = 0;
    // 哈希函数个数
    int32_t k_ = 0;
    std::string bloomfilter_data_;
};

BloomFilter::BloomFilter(int32_t bits_per_key) : bits_per_key_(bits_per_key) {
    CalcHashNum();
}

BloomFilter::BloomFilter(int32_t entries_num, float positive) {
    if (entries_num > 0) {
        CalcBloomBitsPerKey(entries_num, positive);
    }
    CalcHashNum();
}

void BloomFilter::CalcHashNum() {
    if (bits_per_key_ < 0) {
        bits_per_key_ = 0;
    }
    k_ = static_cast<int32_t>(bits_per_key_ *
                              0.69314718056);  // 0.69314718056 =~ ln(2)
    k_ = k_ < 1 ? 1 : k_;
    k_ = k_ > 30 ? 30 : k_;
}

void BloomFilter::CalcBloomBitsPerKey(int32_t entries_num, float positive) {
    float size = -1 * entries_num * logf(positive) / powf(0.69314718056, 2.0);
    bits_per_key_ = static_cast<int32_t>(ceilf(size / entries_num));
}

const char *BloomFilter::Name() { return "general_bloomfilter."; }

void BloomFilter::CreateFilter(const std::string_view *keys, int32_t n) {
    if (n <= 0 || !keys) {
        return;
    }

    int32_t bits = n * bits_per_key_;
    bits = bits < 64 ? 64 : bits;
    const int32_t bytes = (bits + 7) / 8;
    bits = bytes * 8;
    //这里主要是在corekv场景下，可能多个bf共用一个底层bloomfilter_data_对象
    const int32_t init_size = bloomfilter_data_.size();
    bloomfilter_data_.resize(init_size + bytes, 0);
    // 转成数组使用起来更方便
    char *array = &(bloomfilter_data_)[init_size];
    for (int i = 0; i < n; i++) {
        // Use double-hashing to generate a sequence of hash values.
        // See analysis in [Kirsch,Mitzenmacher 2006].
        uint32_t hash_val = hash_util::SimMurMurHash(keys[i].data(), keys[i].size());
        const uint32_t delta =
                (hash_val >> 17) | (hash_val << 15);  // Rotate right 17 bits
        for (size_t j = 0; j < k_; j++) {
            const uint32_t bitpos = hash_val % bits;
            array[bitpos / 8] |= (1 << (bitpos % 8));
            hash_val += delta;
        }
    }
}

bool BloomFilter::MayMatch(const std::string_view &key, int32_t start_pos,
                           int32_t len) {
    if (key.empty() || bloomfilter_data_.empty()) {
        return false;
    }
    // 转成
    const char *array = bloomfilter_data_.data();
    const size_t total_len = bloomfilter_data_.size();
    if (start_pos >= total_len) {
        return false;
    }
    if (len == 0) {
        len = total_len - start_pos;
    }
    std::string_view bloom_filter(array + start_pos, len);
    const char *cur_array = bloom_filter.data();
    const int32_t bits = len * 8;
    if (k_ > 30) {
        return true;
    }

    uint32_t hash_val = hash_util::SimMurMurHash(key.data(), key.size());
    const uint32_t delta =
            (hash_val >> 17) | (hash_val << 15);  // Rotate right 17 bits
    for (int32_t j = 0; j < k_; j++) {
        const uint32_t bitpos = hash_val % bits;
        if ((cur_array[bitpos / 8] & (1 << (bitpos % 8))) == 0) {
            return false;
        }
        hash_val += delta;
    }
    return true;
}
