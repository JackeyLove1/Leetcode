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

