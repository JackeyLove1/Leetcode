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

// usages 
// std::string_view sv = "abc";
// cout << Hash(sv.data(), sv.size()) << endl;