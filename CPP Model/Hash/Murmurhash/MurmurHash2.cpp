#include <stdint.h>
#include <stdlib.h>

uint32_t MurmurHash(const char* ptr, size_t size) {
    const uint32_t k = 1540483477;
    uint32_t h = size;
    uint32_t x = 0;
    const uint32_t* p = reinterpret_cast<const uint32_t*>(ptr);
    while (size >= 4) {
        x = *p;
        x *= k;
        x ^= x >> 24;
        x *= k;
        h *= k;
        h ^= x;
        ++p;
        size -= 4;
    }
    ptr = reinterpret_cast<const char*>(p);
    switch (size) {
        case 3:
            h ^= ptr[2] << 16;
        case 2:
            h ^= ptr[1] << 8;
        case 1:
            h ^= ptr[0];
            h *= 0x5bd1e995;
    }
    h ^= h >> 13;
    h *= 0x5bd1e995;
    h ^= h >> 15;
    return h;
}

uint32_t XXHash(const char* ptr, size_t size) {
    // Primes
    static const uint32_t k1 = 2654435761U;
    static const uint32_t k2 = 2246822519U;
    static const uint32_t k3 = 3266489917U;
    static const uint32_t k4 = 668265263U;
    static const uint32_t k5 = 374761393U;

    const uint32_t* p = reinterpret_cast<const uint32_t*>(ptr);
    const uint32_t* end = reinterpret_cast<const uint32_t*>(ptr + size);
    uint32_t h = k5;

    #define XX_ROT32(x, r) (((x) << (r)) | ((x) >> (32 - (r))))
    if (size >= 16) {
        const uint32_t* limit = end - 4;
        uint32_t v1 = k1 + k2;
        uint32_t v2 = k2;
        uint32_t v3 = 0;
        uint32_t v4 = 0 - k1;
        do {
            v1 += *p++ * k2, v1 = XX_ROT32(v1, 13), v1 *= k1;
            v2 += *p++ * k2, v2 = XX_ROT32(v2, 13), v2 *= k1;
            v3 += *p++ * k2, v3 = XX_ROT32(v3, 13), v3 *= k1;
            v4 += *p++ * k2, v4 = XX_ROT32(v4, 13), v4 *= k1;
        } while (p <= limit);
        h = XX_ROT32(v1, 1) + XX_ROT32(v2, 7) +
            XX_ROT32(v3, 12) + XX_ROT32(v4, 18);
    }

    h += size;
    while (p <= end - 1) {
        h += *p++ * k3;
        h = XX_ROT32(h, 17) * k4;
    }

    const char* q = reinterpret_cast<const char*>(p);
    const char* e = reinterpret_cast<const char*>(end);
    while (q < e) {
        h += *q++ * k5;
        h = XX_ROT32(h, 11) * k1;
    }

    h ^= h >> 15;
    h *= k2;
    h ^= h >> 13;
    h *= k3;
    h ^= h >> 16;
    #undef XX_ROT32
    return h;
}

uint32_t Djb2Hash(const char *ptr, size_t size) {
    uint32_t hash = 5381;
    size_t i = 0;
    while (++i <= size) {
        hash = ((hash << 5) + hash) + *ptr++;  // hash * 33 + c
    }
    return hash;
}

uint32_t FNVHash(const char* ptr, size_t size) {
    uint32_t hash = 1;
    for (size_t i = 0; i < size; ++i) {
        hash *= 2166136261;
        hash ^= (*ptr);
    }
    return hash;
}